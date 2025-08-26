#include "s21_matrix_exception.h"

namespace s21 {

MatrixException::MatrixException(ErrorType errorType) {
    switch (errorType) {
    case ErrorType::ZeroSizeMatrices:
        message_ = "The size of the matrices is zero";
        break;
    case ErrorType::ZeroSizeThisMatrix:
        message_ = "The size of the \"matrix(this)\" is zero";
        break;
    case ErrorType::ZeroSizeOtherMatrix:
        message_ = "The size of the \"matrix(other)\" is zero";
        break;
    case ErrorType::DifferentRowsAndColumns:
        message_ = "Different number of rows and columns in \"this->matrix_\" and \"other.matrix\"";
        break;
    case ErrorType::DifferentColumns:
        message_ = "Different number of columns in \"this->matrix_\" and \"other.matrix\"";
        break;
    case ErrorType::DifferentRows:
        message_ = "Different number of rows in \"this->matrix_\" and \"other.matrix\"";
        break;
    case ErrorType::IncompatibleMatrixDimensions:
        message_ = "The number of columns of the first matrix is not equal to the number of rows of the second matrix";
        break;
    case ErrorType::IndexExceedsDimensions:
        message_ = "Index exceeds matrix dimensions";
        break;
    case ErrorType::InvalidIndexValue:
        message_ = "Invalid index value (index < 0)";
        break;
    case ErrorType::NonSquareMatrix:
        message_ = "The matrix is not square (rows != cols)";
        break;
    case ErrorType::MatrixIsZero:
        message_ = "Determine the matrix is zero";
        break;
    default:
        message_ = "Unknown error";
        break;
    }
}

}  // namespace s21
