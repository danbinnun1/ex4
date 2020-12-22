#pragma once

class ClientHandler {
public:
  virtual void serveClient(const int connfd) = 0;
  virtual ~ClientHandler() = default;
};