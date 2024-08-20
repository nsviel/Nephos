#include "Job.h"

/*
One time job thread
once done it does not rerun
*/


namespace sys::thread{

//Constructor / Destructor
Job::Job(){
  //---------------------------

  this->done = false;
  this->run = false;

  //---------------------------
}
Job::~Job(){
  //---------------------------

  this->wait_thread();

  //---------------------------
}

//Mainfunction
void Job::start_thread(){
  //---------------------------

  this->run_thread();

  //---------------------------
}
void Job::wait_thread(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] {return done.load();});
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Job::run_thread(){
  //---------------------------

  std::lock_guard<std::mutex> lock(mtx);
  if(done || run) return;
  this->run = true;
  this->thread = std::thread(&Job::loop_thread, this);

  //---------------------------
}
void Job::loop_thread(){
  //---------------------------

  this->thread_function();

  {
    std::lock_guard<std::mutex> lock(mtx);
    this->done = true;
    this->run = false;
    cv.notify_all();
  }

  //---------------------------
}

}
