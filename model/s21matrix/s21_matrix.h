/*
 @file s21_matrix_oop.h
 @author professo
 @copyright s21
*/

#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_
#include <cstddef>

#include "s21_matrix_exception.h"

#define EPSILON 1.0e-7

namespace matrix {

class S21Matrix {
 public:
  struct DefaultAllocator {
   static double* allocate(size_t n) {
       return new double[n]();
   }
   static void deallocate(double* p) {
    delete[] p;
   }
  };

  S21Matrix() noexcept : rows_(0), cols_(0), m_alloc(nullptr), matrix_(nullptr){};

  template <typename Allocator = DefaultAllocator>
  explicit S21Matrix(int rows, int cols, const Allocator& alloc = Allocator())
      : rows_(rows), cols_(cols), m_alloc(nullptr), matrix_(nullptr) {
      size_t pointers_size = rows * sizeof(double*);
      size_t data_size = rows * cols * sizeof(double);
      size_t total_size = pointers_size + data_size;

      void* block = nullptr;
      try {
          CheckDimensionMatrices();
          if constexpr (std::is_same_v<Allocator, DefaultAllocator>) {
              block = ::operator new(total_size);
          } else {
              block = alloc.allocate(total_size);
          }

          double** pointers = static_cast<double**>(block);
          double* data = reinterpret_cast<double*>(static_cast<char*>(block) + pointers_size);

          for (int i = 0; i < rows; ++i) {
              pointers[i] = data + i * cols;
          }

          m_alloc = block;
          matrix_ = pointers;
          rows_ = rows;
          cols_ = cols;
      } catch (MatrixException& e) {
          std::throw_with_nested(
              MatrixException("Constructor S21Matrix(...) -> " + std::string(e.what())));
      } catch (...) {
          if (block) {
              if constexpr (std::is_same_v<Allocator, DefaultAllocator>) {
                  ::operator delete(block);
              } else {
                  alloc.deallocate(static_cast<double*>(block), total_size);
              }
          }
          throw;
      }
  }
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  int GetRows() const noexcept { return rows_; }
  int GetCols() const noexcept { return cols_; }
  void SetRows(int const rows);
  void SetCols(int const cols);

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  const double* Get() const;

  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  double operator()(int i, int j) const;
  double& operator()(int i, int j);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double number) const noexcept;
  friend S21Matrix operator*(double number, const S21Matrix& matrix) noexcept;
  S21Matrix& operator*=(double number);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);

  double* Data() noexcept;
  const double* Data() const noexcept;
  bool IsContinuous() const noexcept;

  private:
  void MemoryAllocationForMatrix(int rows, int cols);
  void FreeMatrix() noexcept;
  void CheckExistenceMatrices(const S21Matrix& other) const;
  void CheckExistenceMatrix() const;
  void CheckDimensionMatrices(const S21Matrix& other) const;
  void CheckDimensionMatrices() const;
  void CheckDimensionMatricesMult(const S21Matrix& other) const;
  void CheckingThatMatrixSquare() const;
  void CheckMatrixIndexBoundaries(const int i, const int j) const;
  S21Matrix MatrixMinor(int index_rows, int index_cols) const;
  double FindMaximumNumberInColumn(int indx_rows, int indx_cols,
                                   int& index_max_el) const;
  double SwapRowsMatrix(int indx_rows, int const indx_cols, int index_max_el);
  void MultiplyRows(int indx_rows, int const indx_cols, double maxValueElement);
  double CalculateByGaussMethod();
  int rows_;
  int cols_;
  void* m_alloc;
  double** matrix_;
};

}  // namespace matrix


#endif  // S21_MATRIX_H_
