#include "Base.h"

#include <Vulkan/Namespace.h>
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

  if(thread_paused.load()){
    this->state = vk::queue::PAUSED;
  }

  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return thread_paused.load() == false || thread_running.load() == false; });

  this->state = vk::queue::WAIT_COMMAND;

  //---------------------------
}
void Base::set_pause(bool value){
  //---------------------------

  //Say the thread to pause
  {
    std::unique_lock<std::mutex> lock(mutex);
    thread_paused.store(value);
    cv.notify_all();
  }

  // If pausing, wait until thread_pause reaches the waiting state
  if(value){
    while(state == vk::queue::SUBMIT_COMMAND){
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }

  //---------------------------
}

}
