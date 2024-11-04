#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#define PORT 1234  // Порт для подключения

int main() {
  int sock = 0;
  struct sockaddr_in serv_addr;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address or Address not supported" << std::endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection failed" << std::endl;
    return -1;
  }

  while (true) {
    char buffer[1024] = {0};
    ssize_t valread = read(sock, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
      std::cout << buffer;
      std::string message(buffer);

      if (message.find("Enter your turn:") != std::string::npos) {
        std::string position;
        std::cin >> position;

        send(sock, position.c_str(), position.size(), 0);
      }

      if (message.find("The server has disconnected.") != std::string::npos) {
        break;
      }
    }
  }
}
