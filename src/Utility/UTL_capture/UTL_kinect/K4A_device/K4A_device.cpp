#include "K4A_device.h"

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_thread/K4A_capture.h>
#include <UTL_capture/UTL_kinect/K4A_thread/K4A_replay.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>


//Constructor / Destructor
K4A_device::K4A_device(){
  //---------------------------

  this->k4a_capture = new K4A_capture();
  this->k4a_replay = new K4A_replay();
  this->k4a_configuration= new K4A_configuration();

  //---------------------------
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::run_capture(){
  //---------------------------

  if(!k4a_capture->is_thread_running()){
    k4a_configuration->make_k4a_configuration(this);
    k4a_capture->start_thread(this);
  }

  //---------------------------
}
void K4A_device::run_replay(string path){
  //---------------------------

  this->info.file_path = path;
  k4a_replay->start_thread(this);

  //---------------------------
}
