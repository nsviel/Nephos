#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/Common.h>

namespace utl::network{class Server;}


namespace vld::utils{

class Server
{
public:
  //Constructor / Destructor
  Server();
  ~Server();

public:
  //Main functions
  bool binding(int port, int packet_size);
  void disconnect();
  vector<int> capture();

private:
  utl::network::Server* sock_server;
};

}
