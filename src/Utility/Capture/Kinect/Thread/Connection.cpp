#include "Connection.h"


namespace util::kinect::thread{

//Constructor / Destructor
Connection::Connection(K4A_swarm* k4a_swarm){
  //---------------------------

  this->k4a_swarm = k4a_swarm;

  //---------------------------
}
Connection::~Connection(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Connection::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Connection::run_thread, this);
  }

  //---------------------------
}

//Subfunction
void Connection::run_thread(){
  //---------------------------

  this->thread_running = true;
  while(thread_running){
    k4a_swarm->refresh_connected_device_list();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  //---------------------------
}
void Connection::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

}
