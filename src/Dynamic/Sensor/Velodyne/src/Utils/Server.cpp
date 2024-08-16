#include "Server.h"

#include <Velodyne/Namespace.h>
#include <Utility/Namespace.h>
#include <Network/Namespace.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <bitset>


namespace vld::utils{

//Constructor / Destructor
Server::Server(){
  //---------------------------

  this->sock_server = new sys::network::Server();

  //---------------------------
}
Server::~Server(){
  //---------------------------

  delete sock_server;

  //---------------------------
}

//Main function
bool Server::binding(int port, int packet_size){
  bool is_binded = sock_server->get_is_binded();
  //---------------------------

  //Stop previsou connection
  this->disconnect();

  //Made new connection
  sock_server->binding(port, packet_size);

  //---------------------------
  return sock_server->get_is_binded();
}
void Server::disconnect(){
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->disconnect();
  }

  //---------------------------
}
std::vector<int> Server::capture(){
  std::vector<int> data_dec;
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->recv_data();
    data_dec = sock_server->get_data_dec();
  }

  //---------------------------
  return data_dec;
}

}
