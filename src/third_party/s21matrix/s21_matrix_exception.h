#ifndef S21_MATRIX_EXCEPTION_H_
#define S21_MATRIX_EXCEPTION_H_

#include <exception>
#include <string>

namespace s21 {

class MatrixException : public std::exception {
public:
    enum class ErrorType {
        ZeroSizeMatrices = 1,
        ZeroSizeThisMatrix,
        ZeroSizeOtherMatrix,
        DifferentRowsAndColumns,
        DifferentColumns,
        DifferentRows,
        IncompatibleMatrixDimensions,
        IndexExceedsDimensions,
        InvalidIndexValue,
        NonSquareMatrix,
        MatrixIsZero
    };

    explicit MatrixException(ErrorType errorType);
    explicit MatrixException(const std::string& msg) : message_(msg) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

}  // namespace s21

#endif  // S21_MATRIX_EXCEPTION_H_
