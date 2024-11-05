#include <string>
#include "Server.hpp"

int ParsePort(int argc, char* argv[]) {
  int port = 0;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--port" && i + 1 < argc) {
      port = std::stoi(argv[i + 1]);
      break;
    }
  }
  return port;
}

int main(int argc, char* argv[]) {
  int port = ParsePort(argc, argv);

  Server server(port);
  server.StartServer();
  server.ReceiveConnections();
}