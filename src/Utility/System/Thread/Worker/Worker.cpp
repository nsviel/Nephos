#include "Worker.h"

#include <Utility/Namespace.h>

/*
Continuous big thread
with init, end and inside while loop
*/


namespace sys::thread{

//Main function
void Worker::start_thread(){
  //---------------------------

  if(!thread_running.load()){
    thread_running.store(true);
    this->thread = std::thread(&Worker::run_thread, this);
  }

  //---------------------------
}
void Worker::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running.load()){
    this->thread_loop();
    this->thread_pause();
  }

  this->thread_end();

  //---------------------------
}
void Worker::stop_thread(){
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
void Worker::thread_pause(){
  //---------------------------

  // Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return !thread_paused.load() || !thread_running.load(); });

  //---------------------------
}
void Worker::set_pause(bool value){
  //---------------------------

  thread_paused.store(value);
  cv.notify_all();

  //---------------------------
}

}
