#include <iostream>
#include "Client.hpp"

std::pair<std::string, int> ParseIpAndPort(int argc, char* argv[]) {
  std::string ip_address;
  int port;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--connect" && i + 1 < argc) {
      std::string address = argv[i + 1];
      auto colon_pos = address.find(':');
      ip_address = address.substr(0, colon_pos);
      port = std::stoi(address.substr(colon_pos + 1));
      break;
    }
  }
  return std::make_pair(ip_address, port);
}

int main(int argc, char* argv[]) {
  std::pair<std::string, int> address = ParseIpAndPort(argc, argv);
  std::string ip = address.first;
  int port = address.second;

  std::cout << "TicTacToe client version 1.0.0\n";
  std::cout << "Connecting server at " << ip << ':' << port << "...\n\n";

  Client client(ip, port);
  client.CreateConnection();
  client.StartReceivingData();
}
