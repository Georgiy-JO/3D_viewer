#include "s21_matrix.h"
#include "s21_matrix_exception.h"

#include <utility>

namespace s21 {

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
    for (int i = 0; i != rows_; ++i) {
        for (int j = 0; j != cols_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), m_alloc(other.m_alloc), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.m_alloc = nullptr;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept {
    FreeMatrix();
}

void S21Matrix::SetRows(int const rows) {
  bool status = false;
  if (matrix_ && rows_ > 0 && cols_ > 0 && rows != rows_) {
    status = true;
  }
  if (status) {
    S21Matrix A(rows, cols_);
    int min_rows = rows < rows_ ? rows : rows_;
    for (int i = 0; i != min_rows; ++i) {
      for (int j = 0; j != cols_; ++j) {
        A(i, j) = matrix_[i][j];
      }
    }
    *this = std::move(A);
  }
}

void S21Matrix::SetCols(int const cols) {
  bool status = false;
  if (matrix_ && cols > 0 && rows_ > 0 && cols != cols_) {
    status = true;
  }
  if (status) {
    S21Matrix A(rows_, cols);
    int min_cols = cols < cols_ ? cols : cols_;
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != min_cols; ++j) {
        A(i, j) = matrix_[i][j];
      }
    }
    *this = std::move(A);
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool status = false;
  status = rows_ == other.rows_ && cols_ == other.cols_ ? true : false;
  if (status && rows_ > 0 && cols_ > 0) {
    for (int i = 0; i != rows_ && status; ++i) {
      for (int j = 0; j != cols_ && status; ++j) {
        status = abs(matrix_[i][j] - other(i, j)) < EPSILON ? true : false;
      }
    }
  }
  return status;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  try {
    CheckExistenceMatrices(other);
    CheckDimensionMatrices(other);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] += other(i, j);
      }
    }
  } catch (MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: SumMatrix(...) -> " + std::string(e.what())));
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  try {
    CheckExistenceMatrices(other);
    CheckDimensionMatrices(other);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] -= other(i, j);
      }
    }
  } catch (MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: SubMatrix(...) -> " + std::string(e.what())));
  }
}

void S21Matrix::MulNumber(const double num) {
  try {
    CheckDimensionMatrices();
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  } catch (MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: MulNumber(...) -> " + std::string(e.what())));
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  try {
    CheckExistenceMatrices(other);
    CheckDimensionMatricesMult(other);
    S21Matrix result(rows_, other.GetCols());
    for (int i = 0; i != result.GetRows(); ++i) {
      for (int j = 0; j != result.GetCols(); ++j) {
        for (int k = 0; k != cols_; k++) {
          result(i, j) += matrix_[i][k] * other(k, j);
        }
      }
    }
    *this = std::move(result);
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: MulMatrix(...) -> " + std::string(e.what())));
  }
}

S21Matrix S21Matrix::Transpose() {
  CheckExistenceMatrix();
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result(i, j) = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix m_result(rows_, cols_);
  try {
    CheckExistenceMatrix();
    CheckingThatMatrixSquare();
    int sign = 1;
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        sign = ((i + 1 + j + 1) % 2) ? -1 : 1;
        S21Matrix MinorMatrix;
        MinorMatrix = MatrixMinor(i, j);
        m_result(i, j) = (MinorMatrix.Determinant() * sign);
      }
    }
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: CalcComplements() -> " + std::string(e.what())));
  }
  return m_result;
}

double S21Matrix::Determinant() {
  double result = 1.0;
  try {
    CheckExistenceMatrix();
    CheckingThatMatrixSquare();

    if (rows_ == 1) {
      result = matrix_[0][0];
    } else if (rows_ == 2) {
        result =  matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      result = CalculateByGaussMethod();
    }
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: Determinant() -> " + std::string(e.what())));
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix m_result;
  double determinant = 0.0;
  try {
    CheckExistenceMatrix();
    CheckingThatMatrixSquare();
    determinant = Determinant();
    if (std::abs(determinant) <= EPSILON) {
      throw MatrixException(MatrixException::ErrorType::MatrixIsZero);
    }
    if (rows_ == 1) {
      m_result = *this;
      m_result(0, 0) = (1 / determinant);
    } else {
      m_result = Transpose().CalcComplements() * (1.0 / determinant);
    }
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: InverseMatrix() -> " + std::string(e.what())));
  }
  return m_result;
}

const double *S21Matrix::Get() const {
    if (matrix_ && matrix_[0]) {
        return matrix_[0];
    }
    return nullptr;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix dublicate(other);
  std::swap(*this, dublicate);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    FreeMatrix();
    std::swap(m_alloc, other.m_alloc);
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
  return *this;
}

double S21Matrix::operator()(int i, int j) const {
  try {
    CheckMatrixIndexBoundaries(i, j);
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("operator()(...) const -> " + std::string(e.what())));
  }
  return matrix_[i][j];
}

double& S21Matrix::operator()(int i, int j) {
  try {
    CheckMatrixIndexBoundaries(i, j);
  } catch (const MatrixException& e) {
    std::throw_with_nested(
        MatrixException("& operator()(...) -> " + std::string(e.what())));
  }
  return matrix_[i][j];
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) const noexcept {
  S21Matrix result = *this;
  result.MulNumber(number);
  return result;
}

S21Matrix operator*(double number, const S21Matrix& matrix_obj) noexcept {
  S21Matrix result = matrix_obj * number;
  return result;
}

S21Matrix& S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

void S21Matrix::MemoryAllocationForMatrix(int rows, int cols) {
  try {
    CheckDimensionMatrices();
    size_t total_size = rows * sizeof(double*) + rows * cols * sizeof(double);
    m_alloc = ::operator new(total_size);
    matrix_ = static_cast<double**>(m_alloc);
    double* data = reinterpret_cast<double*>(matrix_ + rows);
    for (int i = 0; i < rows; ++i) {
        matrix_[i] = data + i * cols;
    }
  } catch (MatrixException& e) {
    std::throw_with_nested(
        MatrixException("Error: MemoryAllocationForMatrix(...) -> " + std::string(e.what())));
  } catch (std::bad_alloc& e) {
    std::throw_with_nested(std::bad_alloc());
  }
}

void S21Matrix::FreeMatrix() noexcept {
  if (m_alloc) {
    ::operator delete(m_alloc);
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
    m_alloc = nullptr;
  }
}

void S21Matrix::CheckExistenceMatrices(const S21Matrix& other) const {
  if (!matrix_ && !other.matrix_) {
    throw MatrixException(MatrixException::ErrorType::ZeroSizeMatrices);
  } else if (!matrix_ && other.matrix_) {
    throw MatrixException(MatrixException::ErrorType::ZeroSizeThisMatrix);
  } else if (matrix_ && !other.matrix_) {
    throw MatrixException(MatrixException::ErrorType::ZeroSizeOtherMatrix);
  }
}

void S21Matrix::CheckExistenceMatrix() const {
  if (!matrix_) {
    throw MatrixException(MatrixException::ErrorType::ZeroSizeThisMatrix);
  }
}

void S21Matrix::CheckDimensionMatricesMult(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw MatrixException(MatrixException::ErrorType::IncompatibleMatrixDimensions);
  }
}

void S21Matrix::CheckingThatMatrixSquare() const {
  if (rows_ != cols_) {
    throw MatrixException(MatrixException::ErrorType::NonSquareMatrix);
  }
}

void S21Matrix::CheckDimensionMatrices(const S21Matrix& other) const {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw MatrixException(MatrixException::ErrorType::DifferentRowsAndColumns);
  } else if (rows_ == other.rows_ && cols_ != other.cols_) {
    throw MatrixException(MatrixException::ErrorType::DifferentColumns);
  } else if (cols_ == other.cols_ && rows_ != other.rows_) {
    throw MatrixException(MatrixException::ErrorType::DifferentRows);
  }
}

void S21Matrix::CheckDimensionMatrices() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw MatrixException(MatrixException::ErrorType::ZeroSizeThisMatrix);
  }
}

void S21Matrix::CheckMatrixIndexBoundaries(const int i, const int j) const {
  if (i >= rows_ || j >= cols_) {
    throw MatrixException(MatrixException::ErrorType::IndexExceedsDimensions);
  } else if (i < 0 || j < 0) {
    throw MatrixException(MatrixException::ErrorType::InvalidIndexValue);
  }
}

double S21Matrix::FindMaximumNumberInColumn(int indx_rows, int const indx_cols,
                                            int& index_max_el) const {
  double maxValueElement = 0.0;
  for (int i = indx_rows; i != rows_; ++i) {
    if ((std::abs((*this)(i, indx_cols)) - maxValueElement) > EPSILON) {
      maxValueElement = std::abs((*this)(i, indx_cols));
      index_max_el = i;
    }
  }
  return maxValueElement;
}

double S21Matrix::SwapRowsMatrix(int indx_rows, int const indx_cols,
                                 int index_max_el) {
  double maxValueElement = 0.0;
  if (index_max_el != indx_rows) {
    for (int j = indx_cols; j != cols_; ++j) {
      maxValueElement = (*this)(indx_cols, j);
      (*this)(indx_rows, j) = (*this)(index_max_el, j);
      (*this)(index_max_el, j) = (-maxValueElement);
    }
  }
  maxValueElement = (*this)(indx_rows, indx_cols);
  return maxValueElement;
}

void S21Matrix::MultiplyRows(int indx_rows, int const indx_cols,
                             double maxValueElement) {
  double commonMult = 0.0;
  for (int i = indx_rows + 1; i != rows_; ++i) {
    commonMult = -((*this)(i, indx_cols)) / maxValueElement;
    matrix_[i][indx_cols] = 0.0;
    for (int j = indx_cols + 1; j != cols_; ++j) {
      matrix_[i][j] += commonMult * (*this)(indx_rows, j);
    }
  }
}

double S21Matrix::CalculateByGaussMethod() {
  bool status = true;
  double result = 1.0;
  double numberMax = 0.0;
  int importIndex = 0;
  S21Matrix B = *this;
  for (int i = 0, j = 0; status && i != rows_ && j != cols_; ++i, ++j) {
    numberMax = B.FindMaximumNumberInColumn(i, j, importIndex);
    if (numberMax > EPSILON) {
      numberMax = B.SwapRowsMatrix(i, j, importIndex);
      B.MultiplyRows(i, j, numberMax);
    } else {
      result = 0.0;
      status = false;
    }
  }
  for (int i = 0; status && i < B.rows_; i++) result *= B(i, i);
  return result;
}

S21Matrix S21Matrix::MatrixMinor(int index_closed_row,
                                 int index_closed_cols) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int count_rows = 0;
  int count_cols = 0;
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      if (i != index_closed_row && j != index_closed_cols) {
        minor(count_rows, count_cols) = matrix_[i][j];
        count_cols++;
      }
    }
    if (i != index_closed_row) {
      count_rows++;
      count_cols = 0;
    }
  }
  return minor;
}

double* S21Matrix::Data() noexcept {
    return matrix_ ? matrix_[0] : nullptr;
}

const double* S21Matrix::Data() const noexcept {
    return matrix_ ? matrix_[0] : nullptr;
}

bool S21Matrix::IsContinuous() const noexcept {
    if (!matrix_ || rows_ <= 0 || cols_ <= 0) return false;

    for (int i = 1; i < rows_; ++i) {
        if (matrix_[i] != matrix_[i-1] + cols_) {
            return false;
        }
    }
    return true;
}

}  // namespace s21
