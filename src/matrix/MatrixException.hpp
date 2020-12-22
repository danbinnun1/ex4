#pragma once
#include <exception>
#include "ErrorCode.h"

namespace matrix{
class MatrixException : public std::exception
{
private:
    ErrorCode m_code;
public:
    MatrixException(ErrorCode);
    const char* what() const noexcept;
};
}