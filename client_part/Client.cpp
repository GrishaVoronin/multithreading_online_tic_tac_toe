#include "Client.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

void Client::CreateConnection() {
  sockaddr_in serv_addr{};

  if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error" << std::endl;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_);

  if (inet_pton(AF_INET, ip_.c_str(), &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address or Address not supported" << std::endl;
  }

  if (connect(sock_, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
    std::cerr << "Connection failed" << std::endl;
  }
}

void Client::StartReceivingData() {
  while (true) {
    char buffer[1024] = {0};
    ssize_t valread = read(sock_, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
      std::cout << buffer;
      std::string message(buffer);

      if (message.find("Enter your turn:") != std::string::npos) {
        std::string position;
        std::cin >> position;

        send(sock_, position.c_str(), position.size(), 0);
      }

      if (message.find("The server has disconnected.") != std::string::npos) {
        break;
      }
    }
  }
}
