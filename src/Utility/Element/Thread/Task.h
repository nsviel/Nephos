#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace utl::thread {

class Task {
public:
  Task() : running(false) {}
  Task(Task&& other) noexcept; // Move constructor
  Task& operator=(Task&& other) noexcept; // Move assignment operator
  ~Task();

public:
  void start(std::function<void()> task);
  void stop();
  void wait();

  bool is_running() const { return running; }

private:
  void run();

private:
  std::function<void()> task;
  std::thread thread;
  std::mutex mtx;
  std::condition_variable cv;
  bool running;
};

}
