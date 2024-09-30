#pragma once

#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <condition_variable>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>


namespace vk::queue{

class Base
{
public:
  //Main function
  void start_thread();
  void stop_thread();

  //State function
  void set_pause(bool value);

  inline bool is_thread_running(){return thread_running;}
  inline void set_thread_pause(bool value){thread_paused = value;}

  virtual void add_command(std::unique_ptr<vk::structure::Command> command){}

private:
  void run_thread();
  void thread_pause();

protected:
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}

  std::atomic<bool> thread_running{false};
  std::atomic<bool> thread_paused{false};
  std::condition_variable cv;
  std::thread thread;
  std::mutex mutex;
};

}
