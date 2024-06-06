#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Dynamic/src/Base/State.h>


namespace dyn::base{

struct Thread{
  //---------------------------

  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();
  void wait_thread();

  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}
  virtual void manage_reset(){}

  inline bool is_thread_running(){return thread_running;}

  std::thread thread;
  bool thread_running = false;

  //---------------------------
};

}
