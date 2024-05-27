#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <bitset>


namespace utl::network{

//Constructor / Destructor
Server::Server(){
  //---------------------------

  this->is_binded = false;

  //---------------------------
}
Server::~Server(){}

//Socket function
void Server::binding(int port_server, int packet_size_max){
  if(is_binded) return;
  //---------------------------

  this->port = port_server;
  this->packet_size = packet_size_max;

  // Creating socket file descriptor
  this->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sock < 0){
    cout << "socket creation failed" << endl;
    exit(EXIT_FAILURE);
  }

  // Filling server information
  sockaddr_in addr;
  addr.sin_family       = AF_INET; // IPv4
  addr.sin_addr.s_addr  = INADDR_ANY;
  addr.sin_port         = htons(port);

  // Set timeout value (5 seconds in this example)
  struct timeval timeout;
  timeout.tv_sec = 0;  // Seconds
  timeout.tv_usec = 500000; // Microseconds
  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1){
    std::cerr << "Error setting socket timeout: " << strerror(errno) << std::endl;
    close(sock);
    return;
  }

  // Bind the socket with the server address
  int binding = bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

  //Check final success
  if(binding == 0){
    this->is_binded = true;
  }else{
    cout << "[error] Socket binding failed for port [" << port << "]" << endl;
    this->is_binded = false;
  }

  //---------------------------
}
void Server::recv_data(){
  //---------------------------

  //Parameter
  char buffer[packet_size] = {0};
  sockaddr_in addr;
  addr.sin_family    = AF_INET; // IPv4
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  unsigned int length = sizeof(addr);

  //Thread blocking: MSG_DONTWAIT / MSG_WAITALL
  int udp_size = recvfrom(sock, buffer, packet_size, MSG_WAITALL, reinterpret_cast<sockaddr*>(&addr), &length);

  //Convert buffer of data into a decimal vector
  packet_dec.clear();
  if(udp_size != 0 && udp_size != 512){
    for(int i=0; i<udp_size; i++){
      bitset<8> octet(buffer[i]);

      int octet_32 = octet.to_ulong();
      packet_dec.push_back(octet_32);
    }
  }

  //---------------------------
}
void Server::disconnect(){
  //---------------------------

  if(is_binded){
    close(sock);
    this->is_binded = false;
  }

  //---------------------------
}

}
