#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>


namespace utl::base {

class Thread {
public:
  //Main function
  void start_thread();
  void stop_thread();
  void wait_thread();

  virtual void update_state(){cv.notify_all();}

  inline bool is_thread_running(){return thread_running;}

private:
  void run_thread();
  void pause_thread();

protected:
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}

  std::atomic<bool> thread_running{false};
  std::atomic<bool> thread_pause{false};
  std::condition_variable cv;
  std::thread thread;
  std::mutex mtx;
};

}
