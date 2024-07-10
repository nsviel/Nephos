#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>


namespace utl::thread {

class Task {
public:
  Task();
  virtual ~Task();

public:
  void start_thread();
  void stop_thread();
  void wait_thread();

  inline bool is_running(){return running;}

protected:
  virtual void thread_function(){}

private:
  void run();

private:
  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  std::atomic<bool> running;
};

}
