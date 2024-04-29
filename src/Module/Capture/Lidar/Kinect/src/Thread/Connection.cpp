#include "Connection.h"

#include <Utility/Namespace.h>
#include <Scene/Namespace.h>
#include <Kinect/Namespace.h>
#include <chrono>


namespace k4n::thread{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->dat_set = new dat::Set();

  //---------------------------
}
Connection::~Connection(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Connection::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Connection::run_thread, this);
  }

  //---------------------------
  this->thread_running = true;
}
void Connection::run_thread(){
  static int nb_dev_old = 0;
  //---------------------------

  //Refresh connected sensors
  while(thread_running){
    //Get number of connected devices
    int current_nb_dev = k4a_device_get_installed_count();
    k4n_struct->device.nb_connected_sensor = current_nb_dev;

    //Action on changement
    if(current_nb_dev != nb_dev_old){
      k4n_struct->device.connected_device_change = true;
      nb_dev_old = current_nb_dev;
    }

    //Little sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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