#include "MatrixException.hpp"
using namespace matrix;

MatrixException::MatrixException(ErrorCode code) : m_code(code) {}

const char *MatrixException::what() const noexcept {
  return error_getErrorMessage(m_code);
}