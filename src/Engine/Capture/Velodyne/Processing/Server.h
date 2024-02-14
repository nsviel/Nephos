#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/common.h>

namespace eng::socket{class Server;}


namespace velodyne{

class Server
{
public:
  //Constructor / Destructor
  Server();
  ~Server();

public:
  //Main functions
  void capture_init(int port, int packet_size);
  void capture_stop();
  vector<int> capture_packet();

private:
  eng::socket::Server* sock_server;
};

}
