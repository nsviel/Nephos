#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


namespace utl::thread{

class Task {
public:
  Task();
  virtual ~Task();

  void start_thread();
  void wait_thread();

protected:
  virtual void thread_function(){}

private:
  void loop_thread();

  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> done;
};

}
