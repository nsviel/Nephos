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
K4A_device* K4A_swarm::create_device_virtual(string path){
  //---------------------------

  K4A_device* k4a_device = new K4A_device();
  k4a_device->index = ID_virtual++;
  k4a_device->is_virtual = true;
  struct_k4a_swarm->vec_device.push_back(k4a_device);
  struct_k4a_swarm->nb_device_virtual++;
  k4a_configuration->find_file_information(k4a_device, path);

  //---------------------------
  return k4a_device;
}
K4A_device* K4A_swarm::create_device_real(int index){
  //---------------------------

  k4a::device device = k4a::device::open(index);
  K4A_device* k4a_device = new K4A_device();
  k4a_device->index = index;
  k4a_device->is_virtual = false;
  k4a_device->serial_number = device.get_serialnum();
  struct_k4a_swarm->vec_device.push_back(k4a_device);
  struct_k4a_swarm->nb_device_real++;

  //---------------------------
  return k4a_device;
}
void K4A_swarm::refresh_connected_device_list(){
  //---------------------------

  const uint32_t nb_device = k4a_device_get_installed_count();

  if(nb_device != nb_connected_device){
    //If no real device create virtual one
    say(nb_device);
    if(nb_device == 0){
      string path = "/home/aether/Desktop/output.mkv";
      K4A_device* device = create_device_virtual(path);
      struct_k4a_swarm->selected_device = device;
      device->run_replay(path);
    }
    //Else keep trace of them and run
    else{
      //Fill connected device list
      struct_k4a_swarm->vec_device.clear();
      for(int i=0; i<nb_device; i++){
        try{
          this->create_device_real(i);
        }
        catch(const int error){
          cout<<"[error] refresh device vector"<<endl;
          continue;
        }
      }

      //Default selection
      struct_k4a_swarm->selected_device = struct_k4a_swarm->vec_device[0];

      //Run all thread
      for(int i=0; i<struct_k4a_swarm->vec_device.size(); i++){
        K4A_device* device = struct_k4a_swarm->vec_device[i];
        if(!device->is_virtual){
          device->run_capture();
        }
      }
    }

    this->nb_connected_device = nb_device;
  }




  //---------------------------
}
