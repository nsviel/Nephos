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
  virtual ~Task();

public:
  //Main function
  void start_thread();
  void stop_thread();
  void wait_thread();

  std::future<bool> get_future();

protected:
  virtual void thread_function(){}

private:
  void loop_thread();

private:
  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> run;
  std::atomic<bool> close;
  std::promise<bool> is_running;
};

}
