#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>


namespace sys::thread {

class Routine {
public:
  Routine();
  ~Routine();

public:
  //Main function
  virtual void start_task();
  void stop_task();
  void wait_task();

  inline bool is_done(){return run;}

private:
  void loop_task();

protected:
  void run_task();
  virtual void thread_task(){}

  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> run;
  std::atomic<bool> close;
};

}
