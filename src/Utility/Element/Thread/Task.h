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
  virtual void start_task();
  void stop_task();
  void wait_task();

  inline bool is_done(){return run;}

protected:
  void loop_task();
  virtual void thread_task(){}

protected:
  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> run;
  std::atomic<bool> close;
};

}
