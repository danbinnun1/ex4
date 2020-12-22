#pragma once
#include "Server.hpp"
namespace server_side{
class SerialServer :public Server
{
public:
    void open(const int port, std::unique_ptr<ClientHandler> handler) override;
};
}