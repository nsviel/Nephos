#include "Sensor.h"


namespace utl::thread{

//Main function
void Sensor::start_thread(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mtx);
  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Sensor::run_thread, this);
  }

  //---------------------------
}
void Sensor::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running){
    this->thread_loop();
  }

  this->thread_end();

  //---------------------------
}
void Sensor::stop_thread(){
  //---------------------------

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->thread_running = false;
  }
  cv.notify_all();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Sensor::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !thread_running; });

  //---------------------------
}

}
