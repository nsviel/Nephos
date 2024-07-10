#pragma once

#include <Utility/Element/Thread/Routine.h>
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
  void add_task(std::unique_ptr<utl::thread::Routine> task);
  bool remove_task(utl::thread::Routine* task);

private:
  std::vector<std::unique_ptr<utl::thread::Routine>> tasks;
  std::mutex mutex;
};

}
