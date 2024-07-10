#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>


namespace utl::thread {

class Task {
public:
  Task();
  ~Task();

public:
  //Main function
  virtual void start_thread();
  void stop_thread();
  void wait_thread();

  std::future<bool> get_future();

protected:
  void loop_thread();
  virtual void thread_function(){}

protected:
  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> run;
  std::atomic<bool> close;
  std::promise<bool> is_running;
};

}
