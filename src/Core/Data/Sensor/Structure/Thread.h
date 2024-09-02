#pragma once

#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>


namespace dat::base::sensor{

class Thread{
public:
  //Destructor
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

  std::atomic<bool> run{false};
  std::atomic<bool> pause{false};
  std::condition_variable cv;
  std::thread thread;
  std::mutex mutex;
};

}
