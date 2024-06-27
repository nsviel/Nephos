#pragma once

// Server side implementation of UDP client-server model

#include <vector>


namespace utl::network{

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

  inline std::vector<int> get_data_dec(){return packet_dec;}
  inline bool get_is_binded(){return is_binded;}
  inline int get_status_code(){return code;}
  inline void set_port(int value){this->port = value;}

private:
  std::vector<int> packet_dec;
  bool is_binded;
  int packet_size;
  int port;
  int sock;
  int code;
};

}
