#include "Server.h"

#include <Velodyne/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Server::Server(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_player = new vld::Player(vld_struct);

  //---------------------------
}
Server::~Server(){}

//Main function
void Server::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Server::run_thread, this);
  }

  //---------------------------
  this->thread_idle = false;
}
void Server::run_thread(){
  this->thread_running = true;
  //---------------------------

  //Server thread
  while(thread_running){

  }

  //---------------------------
  this->thread_idle = true;
}
void Server::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction


}
