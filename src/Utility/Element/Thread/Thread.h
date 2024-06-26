#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>


namespace utl::base{

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
  virtual void update_state(){cv.notify_all();}
  virtual void manage_reset(){}

  inline bool is_thread_running(){return thread_running;}

  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  bool thread_running = false;

  //---------------------------
};

}
