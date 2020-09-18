#include "ServerException.hpp"

server_side::ServerException::ServerException(const std::string error)
    : m_error(error) {}

const char* server_side::ServerException::what() const noexcept{
    return m_error.c_str();
}