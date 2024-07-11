#include "Task.h"

#include <Utility/Namespace.h>


namespace utl::thread{

//Main function
void Task::start_thread(){
  //---------------------------

  if(!thread_running.load()){
    thread_running.store(true);
    this->thread = std::thread(&Task::run_thread, this);
  }

  //---------------------------
}
void Task::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running.load()){
    this->thread_loop();
    this->thread_pause();
  }

  this->thread_end();

  //---------------------------
}
void Task::stop_thread(){
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
void Task::thread_pause(){
  //---------------------------

  // Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return !thread_paused.load() || !thread_running.load(); });

  //---------------------------
}
void Task::set_pause(bool value){
  //---------------------------

  thread_paused.store(value);
  cv.notify_all();

  //---------------------------
}

}
