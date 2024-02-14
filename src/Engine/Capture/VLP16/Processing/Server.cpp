#include "Server.h"

#include "../../IO/Socket/Socket_server.h"
#include "../../IO/Socket/Socket_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <bitset>


namespace eng::vlp16{

//Constructor / Destructor
Server::Server(){
  //---------------------------

  this->sock_server = new Socket_server();
  this->sock_client = new Socket_client();

  //---------------------------
}
Server::~Server(){
  //---------------------------

  delete sock_server;
  delete sock_client;

  //---------------------------
}

//Main function
void Server::capture_init(int port, int packet_size){
  bool is_binded = sock_server->get_is_binded();
  //---------------------------

  //Stop previsou connection
  this->capture_stop();

  //Made new connection
  sock_server->socket_binding(port, packet_size);

  //---------------------------
}
void Server::capture_stop(){
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->socket_disconnect();
    sock_server->socket_disconnect();
  }

  //---------------------------
}
vector<int> Server::capture_packet(){
  vector<int> data_dec;
  //---------------------------

  if(sock_server->get_is_binded()){
    sock_server->socket_recv_data();
    data_dec = sock_server->get_data_dec();
  }

  //---------------------------
  return data_dec;
}

}
