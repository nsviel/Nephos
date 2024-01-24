#include "Connection.h"

#include <Utility/Function/File/Info.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n::dev{

//Constructor / Destructor
Connection::Connection(eng::k4n::Node* k4n_node){
  //---------------------------

  this->k4n_swarm = k4n_node->get_k4n_swarm();

  //---------------------------
}
Connection::~Connection(){}

//Main function
void Connection::refresh_connected_dev(){
  //---------------------------

  const uint32_t current_nb_dev = k4a_device_get_installed_count();
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

  //---------------------------
}

//Subfunction
void Connection::manage_new_dev(int nb_new_dev){
  //---------------------------

  eng::k4n::dev::Master* master = k4n_swarm->get_or_create_master("capture");

  //If previsouly no device, we need to supress all default playback
  if(nb_dev == 0){
    k4n_swarm->close_sensor_all(master);
  }

  //Create required number of new devices
  for(int i=0; i<nb_new_dev; i++){
    k4n_swarm->create_sensor_capture();
  }

  //---------------------------
}
void Connection::manage_less_dev(int nb_less_dev){
  //---------------------------

  eng::k4n::dev::Master* master = k4n_swarm->get_master_by_name("capture");

  //Suppress all devices
  k4n_swarm->close_sensor_all(master);

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
