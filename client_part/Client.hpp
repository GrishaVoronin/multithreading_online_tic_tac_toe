#pragma once
#include <string>
#include <unistd.h>

class Client {
public:
  Client(std::string ip, int port) : ip_(std::move(ip)), port_(port) {}
  ~Client() { close(sock_); }
  void CreateConnection();
  void StartReceivingData();
private:
  std::string ip_;
  int port_;
  int sock_ = 0;
};



