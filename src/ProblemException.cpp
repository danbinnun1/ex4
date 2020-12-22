#include "ProblemException.hpp"

server_side::ProblemException::ProblemException(ErrorCode code)
    : m_code(code) {}

int server_side::ProblemException::getCode() const { return m_code; }