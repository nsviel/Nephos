#include "Thread.h"


namespace utl::base{

//Main function
void Thread::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Thread::run_thread, this);
  }

  //---------------------------
}
void Thread::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running){
    this->thread_loop();
  }

  this->thread_end();

  //---------------------------
}
void Thread::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->update_state();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Thread::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_running == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
