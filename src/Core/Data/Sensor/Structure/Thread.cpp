#include "Thread.h"

#include <Utility/Namespace.h>


namespace dat::sensor{

//Destructor
Thread::Thread(){
  //---------------------------

  this->fps_control = new sys::fps::Control(120);

  //---------------------------
}
Thread::~Thread(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Thread::start_thread(){
  //---------------------------

  if(!run.load()){
    run.store(true);
    this->thread = std::thread(&Thread::run_thread, this);
  }

  //---------------------------
}
void Thread::stop_thread(){
  //---------------------------

  //Stop signal
  run.store(false);
  cv.notify_all();

  //Wait termination
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Thread::pause_thread(bool value){
  //---------------------------

  pause.store(value);
  cv.notify_all();

  //---------------------------
}

//Subfunction
void Thread::run_thread(){
  //---------------------------

  this->thread_init();

  while(run.load()){
    fps_control->set_fps_max(30);
    fps_control->start_loop();

    this->thread_loop();
    this->thread_pause();

    fps_control->stop_loop();
  }

  this->thread_end();

  //---------------------------
}
void Thread::thread_pause(){
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return !pause.load() || !run.load(); });

  //---------------------------
}

}
