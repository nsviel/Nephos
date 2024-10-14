#include "Base.h"

#include <Utility/Namespace.h>

/*
Continuous big thread
with init, end and inside while loop
*/


namespace vk::queue{

//Main function
void Base::start_thread(){
  //---------------------------

  if(!thread_running.load()){
    thread_running.store(true);
    this->thread = std::thread(&Base::run_thread, this);
  }

  //---------------------------
}
void Base::run_thread(){
  //---------------------------

  this->thread_init();

  while(thread_running.load()){
    this->thread_loop();
    this->thread_pause();
  }

  this->thread_end();

  //---------------------------
}
void Base::stop_thread(){
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
void Base::thread_pause(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  waiting_for_pause.store(true);  // Indicate thread_pause is about to wait
  cv_pause.notify_all();          // Notify set_pause that thread_pause is ready

  // Wait for command
  cv.wait(lock, [this] { return !thread_paused.load() || !thread_running.load(); });

  waiting_for_pause.store(false); // Reset the flag when exiting wait

  //---------------------------
}
void Base::set_pause(bool value){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  thread_paused.store(value);

  // Wait until thread_pause is in a waiting state before notifying
  cv_pause.wait(lock, [this] { return waiting_for_pause.load(); });

  cv.notify_all();

  //---------------------------
}

}
