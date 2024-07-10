#pragma once

#include <Utility/Element/Thread/Task.h>
#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>


namespace utl::thread {

class Pool0 {
public:
  Pool0();
  ~Pool0();

  //Main function
  void run();
  void wait();

  //Subfunction
  void add_task(std::unique_ptr<utl::thread::Task> task);
  bool remove_task(utl::thread::Task* task);

private:
  void worker_thread();

private:
  std::vector<std::unique_ptr<utl::thread::Task>> tasks;
  std::mutex mutex;
};

}
