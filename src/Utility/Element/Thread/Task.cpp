#include "Task.h"


namespace utl::thread {

//Constructor / Destructor
Task::Task() : running(false){}
Task::~Task(){
  stop_thread();
}

void Task::start_thread(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mtx);
  if(!running){
    running = true;
    thread = std::thread(&Task::run, this);
  }

  //---------------------------
}

void Task::stop_thread(){
  //---------------------------

  {
    std::lock_guard<std::mutex> lock(mtx);
    running = false;
  }
  cv.notify_all();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

void Task::wait_thread(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !running; });

  //---------------------------
}
void Task::run(){
  //---------------------------

  thread_function(); // Call the overridden function
  {
    std::lock_guard<std::mutex> lock(mtx);
    running = false;
  }
  cv.notify_all();

  //---------------------------
}

}
