#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

// Server side implementation of UDP client-server model

#include "../../../common.h"


namespace eng::socket{

class Server
{
public:
  //Constructor / Destructor
  Server();
  ~Server();

public:
  //Socket functions
  void binding(int port, int packet_size);
  void recv_data();
  void disconnect();

  inline vector<int> get_data_dec(){return packet_dec;}
  inline bool get_is_binded(){return is_binded;}
  inline int get_status_code(){return code;}
  inline void set_port(int value){this->port = value;}

private:
  vector<int> packet_dec;
  bool is_binded;
  int packet_size;
  int port;
  int sock;
  int code;
};

}

#endif
