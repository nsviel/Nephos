#include "Thread.h"


namespace dat::base::sensor{

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
/*
  //If pause, wait until end pause or end thread
  if(state.pause || !state.play){
    profiler.pause = true;
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !state.pause || !thread_running;});
    profiler.pause = false;
  }
*/
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
