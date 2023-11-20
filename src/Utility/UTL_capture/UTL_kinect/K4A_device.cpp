#include "K4A_device.h"


//Constructor / Destructor
K4A_device::K4A_device(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::open_selected_device(){
  //---------------------------

  try{
    if (selected_device_idx < 0){return;}
    selected_device = k4a::device::open(static_cast<uint32_t>(selected_device_idx));
  }
  catch (const int error){
    return;
  }

  //---------------------------
}
void K4A_device::refresh_device_list(){
  //---------------------------

  //"(No available devices)"
  const uint32_t nb_device = k4a_device_get_installed_count();

  for (uint32_t i = 0; i < nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);
      connected_device.emplace_back(std::make_pair(i, device.get_serialnum()));
    }
    catch(const int error){
      continue;
    }
  }

  if (!connected_device.empty()){
    selected_device_idx = connected_device[0].first;
  }

  //---------------------------
}
