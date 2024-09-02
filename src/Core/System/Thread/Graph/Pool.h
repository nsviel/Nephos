#pragma once

#include <condition_variable>
#include <functional>
#include <queue>
#include <atomic>
#include <vector>
#include <thread>
#include <future>
#include <mutex>


namespace thr::gph{

class Pool
{
public:
  // Constructor / Destructor
  Pool(int size);
  ~Pool();

public:
  // Submit a function for execution
  template<class F>
  void submit(F&& f) {
    {
      std::unique_lock<std::mutex> lock(mutex);
      if (stop)
        throw std::runtime_error("submit on stopped ThreadPool");

      // Define the task without a promise or exception handling
      auto task = [f = std::forward<F>(f)]() {
        f(); // Execute the task
      };

      queue_task.push(std::move(task));
    }
    cv.notify_one();
  }

private:
  void worker_init(int size);
  void worker_thread();
  void worker_stop();

private:
  std::vector<std::thread> vec_worker;
  std::queue<std::function<void()>> queue_task;
  std::condition_variable cv;
  std::mutex mutex;
  std::atomic<bool> stop;
};

}
