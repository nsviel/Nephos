#pragma once

#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

namespace sys::thread{class Routine;}


namespace sys::thread::routine{

class Pool {
public:
  Pool();
  ~Pool();

  //Main function
  void run();
  void wait();

  //Subfunction
  void add_task(std::unique_ptr<sys::thread::Routine> task);
  bool remove_task(sys::thread::Routine* task);

private:
  std::vector<std::unique_ptr<sys::thread::Routine>> tasks;
  std::mutex mutex;
};

}
