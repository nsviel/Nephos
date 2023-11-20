#include "K4A_device.h"

#include "Struct_kinect.h"


//Constructor / Destructor
K4A_device::K4A_device(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
  this->refresh_device_list();
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::refresh_device_list(){
  //---------------------------

  struct_kinect->vec_device.clear();

  const uint32_t nb_device = k4a_device_get_installed_count();
  for(int i=0; i<nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);

      Struct_k4a_device struct_device;
      struct_device.index = i;
      struct_device.serial_number = device.get_serialnum();
      struct_kinect->vec_device.push_back(struct_device);
    }
    catch(const int error){
      cout<<"[error] refresh device vector"<<endl;
      continue;
    }
  }

  //---------------------------
}
