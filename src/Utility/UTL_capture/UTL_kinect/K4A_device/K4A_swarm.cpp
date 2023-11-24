#include "K4A_swarm.h"

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>


//Constructor / Destructor
K4A_swarm::K4A_swarm(Struct_k4a_swarm* struct_k4a_swarm){
  //---------------------------

  this->struct_k4a_swarm = struct_k4a_swarm;
  this->k4a_configuration= new K4A_configuration();

  //---------------------------
}
K4A_swarm::~K4A_swarm(){}

//Main function
K4A_device* K4A_swarm::create_virtual_device(string path){
  //---------------------------

  K4A_device* device = new K4A_device();
  device->is_virtual = true;
  struct_k4a_swarm->vec_device.push_back(device);
  k4a_configuration->find_file_information(device, path);

  //---------------------------
  return device;
}
void K4A_swarm::refresh_connected_device_list(){
  //---------------------------

  //Fill vec device
  struct_k4a_swarm->vec_device.clear();
  const uint32_t nb_device = k4a_device_get_installed_count();
  for(int i=0; i<nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);

      K4A_device* struct_device = new K4A_device();
      struct_device->index = i;
      struct_device->is_virtual = false;
      struct_device->serial_number = device.get_serialnum();
      struct_k4a_swarm->vec_device.push_back(struct_device);
    }
    catch(const int error){
      cout<<"[error] refresh device vector"<<endl;
      continue;
    }
  }

  //Default selection
  if(nb_device > 0){
    struct_k4a_swarm->selected_device = struct_k4a_swarm->vec_device[0];
  }

  //---------------------------
}
