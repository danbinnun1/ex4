#pragma once
#include <exception>
#include <string>
namespace server_side{
    class ServerException : public std::exception
    {
    private:
        std::string m_error;
    public:
        ServerException(const std::string);
        const char* what() const noexcept override;
    };
}