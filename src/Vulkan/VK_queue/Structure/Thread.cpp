#include "Thread.h"

#include <Utility/Namespace.h>

/*
Continuous big thread
with init, end and inside while loop
*/


namespace vk::queue{

//Main function
void Thread::start_thread(){
  //---------------------------

  if(!thread_running.load()){
    thread_running.store(true);
    this->thread = std::thread(&Thread::run_thread, this);
  }

  //---------------------------
}
void Thread::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running.load()){
    this->thread_loop();
    this->thread_pause();
  }

  this->thread_end();

  //---------------------------
}
void Thread::stop_thread(){
  //---------------------------

  //Stop signal
  thread_running.store(false);
  cv.notify_all();

  //Wait termination
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//State function
void Thread::thread_pause(){
  //---------------------------

  // Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return !thread_paused.load() || !thread_running.load(); });

  //---------------------------
}
void Thread::set_pause(bool value){
  //---------------------------

  thread_paused.store(value);
  cv.notify_all();

  //---------------------------
}

}
