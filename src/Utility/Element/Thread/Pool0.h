#pragma once

#include "Task.h"
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace utl::thread {

class Pool0 {
public:
  Pool0(int nb_threads);
  ~Pool0();

  void add_task(std::function<void()> task);
  void wait_all();

private:
  std::vector<Task> tasks;
  std::queue<std::function<void()>> queue_task;
  std::mutex mutex;
  std::condition_variable condition;
  bool running;
};

}
