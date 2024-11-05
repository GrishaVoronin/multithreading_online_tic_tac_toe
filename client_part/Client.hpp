#pragma once
#include <string>
#include <utility>

class Client {
public:
  Client(std::string ip, int port) : ip_(std::move(ip)), port_(port) {}
  void CreateConnection();
  void StartReceivingData();
private:
  std::string ip_;
  int port_;
  int sock_ = 0;
};



