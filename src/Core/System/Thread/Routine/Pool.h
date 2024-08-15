#pragma once

#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

namespace utl::thread{class Routine;}


namespace utl::thread::routine{

class Pool {
public:
  Pool();
  ~Pool();

  //Main function
  void run();
  void wait();

  //Subfunction
  void add_task(std::unique_ptr<utl::thread::Routine> task);
  bool remove_task(utl::thread::Routine* task);

private:
  std::vector<std::unique_ptr<utl::thread::Routine>> tasks;
  std::mutex mutex;
};

}
