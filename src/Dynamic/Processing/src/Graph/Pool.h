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
  void submit(F&& f){
    //---------------------------

    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      if (stop)
        throw std::runtime_error("submit on stopped ThreadPool");
      tasks.emplace(std::forward<F>(f));
    }
    condition.notify_one();

    //---------------------------
  }

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::condition_variable condition;
  std::mutex queue_mutex;
  bool stop = false;
};

}
