#pragma once
#include "Matrix.h"

namespace matrix {
class Matrix {
  PMatrix m_matrix;

private:
  // checks the result code of a matrix operation and throws exception if needs
  static void checkMatrixCall(ErrorCode);

public:
  // initializes matrix with height and width
  Matrix(const uint32_t height, const uint32_t width);

  // initializes matrix from another matrix
  Matrix(PMatrix matrix);

  // return matrix height
  uint32_t getHeight() const;
  // return matrix width
  uint32_t getWidth() const;

  // adds two matrixes
  Matrix operator+(const Matrix &other) const;
  // multiplies two matrixes
  Matrix operator*(const Matrix &other) const;
  // multiplies a matrix with a scalar
  void operator*=(const double);
  // return matrix value by height and width
  double operator()(const uint32_t row, const uint32_t col) const;
  // sets matrix value
  void setValue(const uint32_t row, const uint32_t col, const double value);
  ~Matrix();
  Matrix(const Matrix&);
  Matrix& operator=(const Matrix&);
  Matrix(Matrix&&);
  Matrix& operator=(Matrix&&);

};
} // namespace matrix