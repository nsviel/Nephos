#pragma once

// Server side implementation of UDP client-server model

#include "../../../common.h"

class Socket_server;
class Socket_client;


namespace eng::vlp16{

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
  Socket_server* sock_server;
  Socket_client* sock_client;
};

}
