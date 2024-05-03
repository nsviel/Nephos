#include "Thread.h"

#include <Data/Namespace.h>


namespace dyn::capture{

//Constructor / Destructor
Thread::Thread(){
  //---------------------------


  //---------------------------
}
Thread::~Thread(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Thread::start_thread(dat::base::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Thread::run_thread, this, sensor);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
}
void Thread::run_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->thread_init(sensor);

  //Thread thread
  while(thread_running){
    this->thread_loop(sensor);
  }

  this->thread_end(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Thread::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Thread::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
