#include "Server.h"

#include <Velodyne/Namespace.h>
#include <Utility/Namespace.h>

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

  this->sock_server = new utl::network::Server();

  //---------------------------
}
Server::~Server(){
  //---------------------------

  delete sock_server;

  //---------------------------
}

//Main function
void Server::binding(int port, int packet_size){
  bool is_binded = sock_server->get_is_binded();
  //---------------------------

  //Stop previsou connection
  this->disconnect();

  //Made new connection
  sock_server->binding(port, packet_size);

  //---------------------------
}
void Server::disconnect(){
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->disconnect();
  }

  //---------------------------
}
vector<int> Server::capture(){
  vector<int> data_dec;
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->recv_data();
    data_dec = sock_server->get_data_dec();
  }

  //---------------------------
  return data_dec;
}

}
