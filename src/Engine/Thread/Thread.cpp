#include "Thread.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace eng::thread{

//Constructor / Destructor
Thread::Thread(bool* running){
  //---------------------------

  this->running = running;

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::start(){
  //---------------------------

  this->thread = std::thread(&Thread::run, this);

  //---------------------------
}
void Thread::run(){
  //---------------------------

  while(*running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Thread::stop(){
  //---------------------------

  this->wait();

  //---------------------------
}
void Thread::wait(){
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

}
