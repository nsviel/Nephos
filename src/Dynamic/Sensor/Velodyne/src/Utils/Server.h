#pragma once

#include <vector>

namespace net::sok{class Server;}

// Server side implementation of UDP client-server model


namespace vld::utils{

class Server
{
public:
  //Constructor / Destructor
  Server();
  ~Server();

public:
  //Main function
  bool binding(int port, int packet_size);
  void disconnect();
  std::vector<int> capture();

private:
  net::sok::Server* sock_server;
};

}
