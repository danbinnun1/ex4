#pragma once
#include "ErrorCode.hpp"
#include <exception>
namespace server_side {
class ProblemException : public std::exception {
private:
  ErrorCode m_code;

public:
  ProblemException(const ErrorCode code);
  int getCode() const;
};
} // namespace server_side