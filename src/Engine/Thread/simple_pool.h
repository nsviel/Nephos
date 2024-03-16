#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class Pool
{
public:
  Pool(size_t numThreads) : running(true){
    //---------------------------

    for (size_t i = 0; i < numThreads; ++i){
      vec_thread.emplace_back(&Pool::workerThreadLoop, this);
    }

    //---------------------------
  }

  ~Pool(){
    //---------------------------

    {
      std::unique_lock<std::mutex> lock(mutex);
      running = false;
    }

    // Notify all vec_thread to stop
    condition.notify_all();
    for(auto& thread : vec_thread){
      thread.join();
    }

    //---------------------------
  }

  void add_task(std::function<void()> task, bool* taskDone = nullptr){
    //---------------------------

    std::unique_lock<std::mutex> lock(mutex);
    queue_task.push([task, taskDone]() {
      // Execute the original task
      task();

      // Set the taskDone flag to true when the task is done
      if(taskDone != nullptr){
        *taskDone = true;
      }
    });

    // Notify one thread to pick up the task
    condition.notify_one();

    //---------------------------
  }

private:
  void workerThreadLoop(){
    //---------------------------

    while(true){
      std::function<void()> task;

      {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [&] { return !queue_task.empty() || !running; });
        if (!running) return;
        task = std::move(queue_task.front());
        queue_task.pop();
      }

      // Execute the task outside the lock
      task();
    }

    //---------------------------
  }

private:
    std::vector<std::thread> vec_thread;
    std::queue<std::function<void()>> queue_task;
    std::mutex mutex;
    std::condition_variable condition;
    bool running;
};
