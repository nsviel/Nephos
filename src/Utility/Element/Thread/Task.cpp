#include "Task.h"

#include <Utility/Namespace.h>


namespace utl::thread {

//Constructor / Destructor
Task::Task(){
  //---------------------------

  this->run = false;
  this->close = false;

  //---------------------------
}
Task::~Task(){
  //---------------------------

  this->stop_task();

  //---------------------------
}

//Main function
void Task::start_task(){
  //---------------------------

  this->wait_task();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;

    // Thread is already running, do nothing
    if (thread.joinable()) return;
    this->thread = std::thread(&Task::loop_task, this);
  }

  cv.notify_all();

  //---------------------------
}
void Task::stop_task(){
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
void Task::wait_task(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return run.load(); });

  //---------------------------
}

//Subfunction
void Task::loop_task(){
  //---------------------------

  while(true){
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this] { return run || close; });

      if(close){
        return;
      }
    }

    // Execute the task
    this->thread_task();

    {
      std::lock_guard<std::mutex> lock(mtx);
      this->run = false;
    }
  }

  //---------------------------
}

}
