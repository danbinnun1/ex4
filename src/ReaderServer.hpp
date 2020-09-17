#pragma once
#include "Server.hpp"
#include <string>
#include <chrono>
namespace server_side
{
    class ReaderServer : public Server
    {
    private:
        //what the client need to send to disconenect
        std::string m_end;
        //maximum amount of clients the server can handle in the same time
        uint32_t m_maxClients;
        //amount of clients connected now
        uint32_t m_currentClients;
        //time to wait for the client to send
        long m_waitTime;
        void serveClient(const int connfd);
    public:
        void open(const int port) override;
        ReaderServer(const std::string& end, uint32_t maxClients, long waitTime);
    };
}