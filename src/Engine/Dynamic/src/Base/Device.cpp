#include "Device.h"

#include <Data/Namespace.h>


namespace dyn::base{

//Constructor / Destructor
Device::Device(){
  //---------------------------


  //---------------------------
}
Device::~Device(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Device::start_thread(){
  if(sensor == nullptr) return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Device::run_thread, this, sensor);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
}
void Device::run_thread(){
  //---------------------------

  this->thread_init(sensor);

  //Device thread
  while(thread_running){
    this->thread_loop(sensor);
  }

  this->thread_end(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Device::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Device::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
