#pragma once

#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>

namespace sys::fps{class Control;}


namespace dat::sensor{

class Thread{
public:
  //Constructor / Destructor
  Thread();
  ~Thread();

public:
  //Main function
  void start_thread();
  void stop_thread();
  void pause_thread(bool value);

  inline bool is_thread_running(){return run.load();}

private:
  //Subfunction
  void run_thread();
  void thread_pause();

protected:
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}

  sys::fps::Control* fps_control;
  std::atomic<bool> run{false};
  std::atomic<bool> pause{false};
  std::condition_variable cv;
  std::thread thread;
  std::mutex mutex;
};

}
