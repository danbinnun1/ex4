#pragma once
#include <Server.hpp>
#include <string>
#include <chrono>
namespace server_side
{
    class ReaderServer : public Server
    {
    private:
        //what the client need to send to disconenect
        std::string end;
        //maximum amount of clients the server can handle in the same time
        uint32_t maxClients;
        //amount of clients connected now
        uint32_t currentClients;
        //time to wait for the client to send
        std::chrono::milliseconds waitTime;
        void serveClient(const int connfd, const std::string& problem, const std::string& alg);
    public:
        void open(int port) override;
    };
}