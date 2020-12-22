#include "Matrix.hpp"
#include "MatrixException.hpp"

void matrix::Matrix::checkMatrixCall(ErrorCode code) {
  if (!error_isSuccess(code)) {
    MatrixException exception(code);
    throw exception;
  }
}

matrix::Matrix::Matrix(const uint32_t height, const uint32_t width) {
  checkMatrixCall(matrix_create(&m_matrix, height, width));
}

matrix::Matrix::Matrix(PMatrix matrix) { this->m_matrix = matrix; }

uint32_t matrix::Matrix::getHeight() const {
  uint32_t height;
  checkMatrixCall(matrix_getHeight(m_matrix, &height));
  return height;
}

uint32_t matrix::Matrix::getWidth() const {
  uint32_t width;
  checkMatrixCall(matrix_getWidth(m_matrix, &width));
  return width;
}

matrix::Matrix matrix::Matrix::operator+(const Matrix &other) const {
  PMatrix result;
  checkMatrixCall(matrix_add(&result, m_matrix, other.m_matrix));
  Matrix additionResult = Matrix(result);
  return additionResult;
}

matrix::Matrix matrix::Matrix::operator*(const Matrix &other) const {
  PMatrix result;
  checkMatrixCall(matrix_multiplyMatrices(&result, m_matrix, other.m_matrix));
  Matrix MultiplicationResult = Matrix(result);
  return MultiplicationResult;
}

void matrix::Matrix::operator*=(const double scalar) {
  checkMatrixCall(matrix_multiplyWithScalar(m_matrix, scalar));
}

double matrix::Matrix::operator()(const uint32_t row, const uint32_t col) const {
  double value;
  checkMatrixCall(matrix_getValue(m_matrix, row, col, &value));
  return value;
}

void matrix::Matrix::setValue(const uint32_t row, const uint32_t col, const double value) {
  checkMatrixCall(matrix_setValue(m_matrix, row, col, value));
}

matrix::Matrix::~Matrix(){
  matrix_destroy(m_matrix);
}

matrix::Matrix::Matrix(const Matrix& other){
  checkMatrixCall(matrix_copy(&m_matrix, other.m_matrix));
}

matrix::Matrix::Matrix(Matrix&& other){
  m_matrix=other.m_matrix;
  other.m_matrix = nullptr;
}

matrix::Matrix& matrix::Matrix::operator=(const Matrix& other){
  if (&other != this) {
        matrix_destroy(m_matrix);
        m_matrix = nullptr;
        matrix_copy(&m_matrix, other.m_matrix);
      }
      return *this;
}

matrix::Matrix& matrix::Matrix::operator=(Matrix&& other){
  if (&other != this) {
        matrix_destroy(m_matrix);
        m_matrix = other.m_matrix;
        other.m_matrix = nullptr;
      }
      return *this;
}
