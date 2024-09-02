#pragma once

#include <condition_variable>
#include <functional>
#include <queue>
#include <atomic>
#include <vector>
#include <thread>
#include <future>
#include <mutex>


namespace dat::sensor{

class Pool
{
public:
  // Constructor / Destructor
  Pool(int size);
  ~Pool();

public:
  // Submit a function for execution
  template<class F>
  std::future<void> submit(F&& f) {
    // Create a promise and future for this task
    auto promise = std::make_shared<std::promise<void>>();
    std::future<void> future = promise->get_future();

    {
      std::unique_lock<std::mutex> lock(mutex);
      if (stop)
        throw std::runtime_error("submit on stopped ThreadPool");

      // Wrap the task to set the promise value upon completion
      auto task = [promise, f = std::forward<F>(f)]() mutable {
        try {
          f(); // Execute the task
          promise->set_value(); // Notify that the task is complete
        } catch (...) {
          promise->set_exception(std::current_exception()); // Notify of any exceptions
        }
      };

      queue_task.push(std::move(task));
    }
    cv.notify_one();
    return future;
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
