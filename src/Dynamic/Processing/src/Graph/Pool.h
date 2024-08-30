#pragma once

#include <condition_variable>
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>


namespace dyn::prc{

class Pool
{
public:
  // Constructor / Destructor
  Pool(size_t num_threads);
  ~Pool();

public:
  //Main function
  template<class F>
  void submit(F&& f);

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::condition_variable condition;
  std::mutex queue_mutex;
  bool stop = false;
};

}
