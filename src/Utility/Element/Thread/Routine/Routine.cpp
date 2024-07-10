#include "Routine.h"

#include <Utility/Namespace.h>


namespace utl::thread {

//Constructor / Destructor
Routine::Routine(){
  //---------------------------

  this->run = false;
  this->close = false;

  //---------------------------
}
Routine::~Routine(){
  //---------------------------

  this->stop_task();

  //---------------------------
}

//Main function
void Routine::start_task(){
  //---------------------------

  this->wait_task();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;
    cv.notify_all();

    // Thread is already running, do nothing
    if (thread.joinable()) return;
    this->thread = std::thread(&Routine::loop_task, this);
  }

  //---------------------------
}
void Routine::stop_task(){
  //---------------------------

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = false;
    this->close = true;
  }

  cv.notify_all();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Routine::wait_task(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !run; });

  //---------------------------
}

//Subfunction
void Routine::loop_task(){
  //---------------------------

  while(true){
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this] { return run || close; });
      if(close) return;
    }

    // Execute the task
    this->thread_task();

    {
      std::lock_guard<std::mutex> lock(mtx);
      this->run = false;
      cv.notify_all();
    }
  }

  //---------------------------
}

}
