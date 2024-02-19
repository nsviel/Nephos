#include "Connection.h"

#include <Utility/Namespace.h>
#include <K4N/Namespace.h>
#include <chrono>


namespace k4n::thread{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();

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
}
void Connection::run_thread(){
  //---------------------------

  //Refresh connected sensors
  this->thread_running = true;
  while(thread_running){
    //Get number of connected devices
    const uint32_t current_nb_dev = k4a_device_get_installed_count();

    //Action on changement
    if(current_nb_dev != nb_dev){
      //If some news, run them
      if(current_nb_dev > nb_dev){
        int number = current_nb_dev - nb_dev;
        this->manage_new_dev(number);
      }
      //If some less, supress them
      else if(current_nb_dev < nb_dev){
        int number = nb_dev - current_nb_dev;
        this->manage_less_dev(number);
      }

      nb_dev = current_nb_dev;
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

//Subfunction
void Connection::manage_new_dev(int nb_new_dev){
  //---------------------------

  k4n::dev::Master* master = k4n_swarm->get_or_create_master("capture");

  //If previsouly no device, we need to supress all default playback
  if(nb_dev == 0){
    master->delete_entity_all();
  }

  //Create required number of new devices
  for(int i=0; i<nb_new_dev; i++){
    k4n_swarm->create_sensor_capture();
  }

  //---------------------------
}
void Connection::manage_less_dev(int nb_less_dev){
  //---------------------------

  k4n::dev::Master* master = k4n_swarm->get_master_by_name("capture");

  //Suppress all devices
  master->delete_entity_all();

  //If no real device create virtual one
  uint32_t current_nb_dev = k4a_device_get_installed_count();
  if(current_nb_dev != 0){
    for(int i=0; i<current_nb_dev; i++){
      k4n_swarm->create_sensor_capture();
    }
  }

  //---------------------------
}

}
