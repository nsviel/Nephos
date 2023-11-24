#include "K4A_connection.h"

#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>


//Constructor / Destructor
K4A_connection::K4A_connection(K4A_swarm* k4a_swarm){
  //---------------------------

  this->k4a_swarm = k4a_swarm;

  //---------------------------
}
K4A_connection::~K4A_connection(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_connection::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_connection::run_thread, this);
  }

  //---------------------------
}

//Subfunction
void K4A_connection::run_thread(){
  //---------------------------

  this->thread_running = true;
  while(thread_running){
    say("check connection");
    k4a_swarm->refresh_connected_device_list();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  //---------------------------
}
void K4A_connection::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
