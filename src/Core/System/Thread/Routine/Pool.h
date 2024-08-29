#pragma once

#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

namespace thr{class Routine;}


namespace thr::routine{

class Pool {
public:
  Pool();
  ~Pool();

  //Main function
  void run();
  void wait();

  //Subfunction
  void add_task(std::unique_ptr<thr::Routine> task);
  bool remove_task(thr::Routine* task);

private:
  std::vector<std::unique_ptr<thr::Routine>> tasks;
  std::mutex mutex;
};

}
