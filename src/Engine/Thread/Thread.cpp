#include "Thread.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace eng::thread{

//Constructor / Destructor
Thread::Thread(){
  //---------------------------

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::start_thread(){
  //---------------------------

  this->thread = std::thread(&Thread::run_thread, this);

  //---------------------------
  this->thread_running = true;
}
void Thread::run_thread(){
  //---------------------------



  //---------------------------
}
void Thread::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->wait_thread();

  //---------------------------
}
void Thread::wait_thread(){
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

}
