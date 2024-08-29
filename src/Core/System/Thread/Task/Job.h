#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


namespace sys::thread{

class Job {
public:
  Job();
  virtual ~Job();

public:
  //Main function
  virtual void start_thread();
  void wait_thread();

private:
  void loop_thread();

protected:
  void run_thread();
  virtual void thread_function(){}

  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> done;
  std::atomic<bool> run;
};

}
