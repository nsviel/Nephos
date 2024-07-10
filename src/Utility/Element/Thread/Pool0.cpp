#include "Pool0.h"


namespace utl::thread {

Pool0::Pool0(int nb_threads) : running(true) {
  //---------------------------

  tasks.reserve(nb_threads); // Reserve space for nb_threads Task objects
  for (int i = 0; i < nb_threads; ++i) {
    tasks.push_back(Task()); // Push back a default-initialized Task object
  }

  //---------------------------
}

Pool0::~Pool0() {
  //---------------------------

  {
    std::unique_lock<std::mutex> lock(mutex);
    running = false;
  }
  condition.notify_all();
  for (auto& task : tasks) {
    task.stop();
  }

  //---------------------------
}

void Pool0::add_task(std::function<void()> task) {
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  // Find the first available task slot and start it
  for (auto& task_instance : tasks) {
    if (!task_instance.is_running()) {
      task_instance.start(std::move(task));
      return;
    }
  }
  // If all tasks are busy, queue the task for later execution
  queue_task.push(std::move(task));
  condition.notify_one();

  //---------------------------
}

void Pool0::wait_all() {
  //---------------------------

  std::unique_lock<std::mutex> lock(mutex);
  for (auto& task : tasks) {
    task.wait();
  }

  //---------------------------
}

}
