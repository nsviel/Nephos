#include "K4A_device.h"

#include <Utility/Capture/Kinect/K4A_thread/K4A_capture.h>
#include <Utility/Capture/Kinect/K4A_thread/K4A_replay.h>



//Constructor / Destructor
K4A_device::K4A_device(){
  //---------------------------

  this->k4a_capture = new K4A_capture();
  this->k4a_replay = new K4A_replay();
  this->k4a_configuration= new util::kinect::device::Configuration();

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
void K4A_device::stop_threads(){
  //---------------------------

  this->k4a_capture->stop_thread();
  this->k4a_replay->stop_thread();

  //---------------------------
}
