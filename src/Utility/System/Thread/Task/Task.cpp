#include "Task.h"

/*
Time-to-time job thread
waiting previous completion before rerunning
*/


namespace sys::thread{

//Constructor / Destructor
Task::Task(){
  //---------------------------

  this->done = false;

  //---------------------------
}
Task::~Task(){
  //---------------------------

  this->wait_thread();

  //---------------------------
}

//Mainfunction
void Task::start_thread(){
  //---------------------------

  this->run_thread();

  //---------------------------
}
void Task::wait_thread(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] {return done.load();});
  if (thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Task::run_thread(){
  //---------------------------

  if(done){
    std::lock_guard<std::mutex> lock(mtx);
    if (thread.joinable()){
      thread.join();
    }
    this->done = false;
    this->thread = std::thread(&Task::loop_thread, this);
  }

  //---------------------------
}
void Task::loop_thread(){
  //---------------------------

  this->thread_function();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->done = true;
    cv.notify_all();
  }

  //---------------------------
}

}
