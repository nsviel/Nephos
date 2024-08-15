#pragma once

#include <vector>

namespace sys::network{class Server;}

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
  sys::network::Server* sock_server;
};

}
