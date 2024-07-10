#include "Task.h"


namespace utl::thread {

//Constructor / Destructor
Task::Task(){
  //---------------------------

  this->run = false;
  this->close = false;
  this->thread = std::thread(&Task::loop_thread, this);

  //---------------------------
}
Task::~Task(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Task::start_thread(){
  //---------------------------

  this->wait_thread();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->run = true;
  }

  cv.notify_all();
  is_running.set_value(true);

  //---------------------------
}
void Task::stop_thread(){
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

  is_running.set_value(false);

  //---------------------------
}
void Task::wait_thread(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !run; });

  //---------------------------
}

//Subfunction
void Task::loop_thread(){
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
    this->thread_function();

    {
      std::lock_guard<std::mutex> lock(mtx);
      this->run = false;
    }

    is_running.set_value(false);
  }

  //---------------------------
}
std::future<bool> Task::get_future(){
  return is_running.get_future();
}

}
