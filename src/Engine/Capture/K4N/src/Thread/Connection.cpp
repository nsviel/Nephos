#include "Connection.h"

#include <Utility/Namespace.h>
#include <Scene/Namespace.h>
#include <K4N/Namespace.h>
#include <chrono>


namespace k4n::thread{

//Constructor / Destructor
Connection::Connection(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  this->struct_k4n = struct_k4n;
  this->k4n_swarm = new k4n::dev::Swarm(struct_k4n);
  this->sce_set = new eng::scene::Set();

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
  static int nb_dev_old = 0;
  //---------------------------

  //Refresh connected sensors
  this->thread_running = true;
  while(thread_running){
    //Get number of connected devices
    int current_nb_dev = k4a_device_get_installed_count();
    struct_k4n->nb_connected_sensor = current_nb_dev;

    //Action on changement
    if(current_nb_dev != nb_dev_old){
      this->manage_new_dev();
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

//Subfunction
void Connection::manage_new_dev(){
  //---------------------------

  //Suppress all devices
  k4n::dev::Master* master = k4n_swarm->get_or_create_capture_master("capture");
  if(master == nullptr) return;
  sce_set->delete_entity_all(master);

  //Retrieve all serial number
  list<Connected_device> list_connected;
  for(int i=0; i<struct_k4n->list_sensor.size(); i++){
    k4a::device device = k4a::device::open(i);

    Connected_device dev_connected;
    dev_connected.serial_number = device.get_serialnum();
    dev_connected.index = i;
    list_connected.push_back(dev_connected);

    device.close();
  }

  //Find those that were not connected
  for(auto sensor : struct_k4n->list_sensor){
    auto it = list_connected.begin();
    while (it != list_connected.end()) {
      Connected_device& dev_connected = *it;

      if(sensor->param.serial_number == dev_connected.serial_number){
        it = list_connected.erase(it); // Remove the element and advance the iterator
      } else {
        ++it; // Move to the next element
      }
    }
  }

  //Create required number of new devices
  for(int i=0; i<list_connected.size(); i++){
    Connected_device& dev_connected = *std::next(list_connected.begin(), i);
    k4n_swarm->create_sensor_capture(dev_connected.serial_number, dev_connected.index);
  }

  //---------------------------
}

}
