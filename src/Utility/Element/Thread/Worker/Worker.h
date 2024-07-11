#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>


namespace utl::thread {

class Worker {
public:
  //Main function
  void start_thread();
  void stop_thread();

  //State function
  void set_pause(bool value);

  inline bool is_thread_running(){return thread_running;}
  inline void set_thread_pause(bool value){thread_paused = value;}

private:
  void run_thread();
  void thread_pause();

protected:
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}

  std::atomic<bool> thread_running{false};
  std::atomic<bool> thread_paused{false};
  std::condition_variable cv;
  std::thread thread;
  std::mutex mutex;
};

}
