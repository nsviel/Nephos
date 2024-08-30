#include "Pool.h"

#include <Thread/Namespace.h>
#include <vector>
#include <queue>


namespace thr{

// Constructor / Destructor
Pool::Pool(int size){
  //---------------------------

  this->worker_init(size);
  this->stop.store(false);

  //---------------------------
}
Pool::~Pool(){
  //---------------------------

  this->worker_stop();

  //---------------------------
}

//Main function
void Pool::worker_init(int size){
  //---------------------------

  for (size_t i = 0; i < size; ++i) {
    //Create and start worker
    vec_worker.emplace_back([this] {
      this->worker_thread();
    });
  }

  //---------------------------
}
void Pool::worker_thread(){
  //---------------------------

  while (true) {
    std::pair<std::function<void()>, std::shared_ptr<std::promise<void>>> task;
    {
      std::unique_lock<std::mutex> lock(mutex);
      cv.wait(lock, [this] { return stop || !queue_task.empty(); });
      if (stop && queue_task.empty())
        return;
      task = std::move(queue_task.front());
      queue_task.pop();
    }
    try {
      task.first(); // Execute the task
      if (task.second) {
        task.second->set_value(); // Notify that the task is complete
      }
    } catch (...) {
      if (task.second) {
        task.second->set_exception(std::current_exception()); // Notify of an exception
      }
    }
  }

  //---------------------------
}
void Pool::worker_stop(){
  //---------------------------

  {
    std::unique_lock<std::mutex> lock(mutex);
    stop = true;
  }
  cv.notify_all();
  for (std::thread &worker : vec_worker){
    worker.join();
  }

  //---------------------------
}

}
