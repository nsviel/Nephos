#include "Worker.h"

#include <Utility/Namespace.h>


namespace utl::thread{

//Main function
void Worker::start_thread(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex);
  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Worker::run_thread, this);
  }

  //---------------------------
}
void Worker::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running){
    this->thread_loop();
    this->thread_pause();
  }

  this->thread_end();

  //---------------------------
}
void Worker::stop_thread(){
  //---------------------------

  {
    std::lock_guard<std::mutex> lock(mutex);
    this->thread_running = false;
  }
  cv.notify_all();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//State function
void Worker::thread_pause(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return !thread_paused || !thread_running;});

  //---------------------------
}
void Worker::set_pause(bool value){
  //---------------------------

  this->thread_paused = value;
  cv.notify_all();

  //---------------------------
}

}
