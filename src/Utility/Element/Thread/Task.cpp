#include "Task.h"


namespace utl::thread {

void Task::start(std::function<void()> task) {
  //---------------------------

  std::lock_guard<std::mutex> lock(mtx);
  if (!running) {
    this->task = std::move(task);
    running = true;
    thread = std::thread(&Task::run, this);
  }

  //---------------------------
}

void Task::stop() {
  //---------------------------

  {
    std::lock_guard<std::mutex> lock(mtx);
    running = false;
  }
  cv.notify_all();
  if (thread.joinable()) {
    thread.join();
  }

  //---------------------------
}

void Task::wait() {
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return !running; });

  //---------------------------
}

void Task::run() {
  //---------------------------

  std::unique_lock<std::mutex> lock(mtx);
  if (task) {
      task();
  }
  running = false;
  cv.notify_all();

  //---------------------------
}

}
