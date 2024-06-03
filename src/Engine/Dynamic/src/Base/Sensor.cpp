#include "Sensor.h"


namespace dyn::base{

//Thread function
void Sensor::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Sensor::run_thread, this);
  }

  //---------------------------
}
void Sensor::run_thread(){
  //---------------------------

  this->thread_init();

  //Sensor thread
  while(thread_running){
    this->thread_loop();
  }

  this->thread_end();

  //---------------------------
}
void Sensor::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Sensor::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
