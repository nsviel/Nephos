#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>
#include <memory>


namespace vk::command::structure{

struct Set{
  //---------------------------

  void wait_until_done(){
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return done; });
  }
  void mark_as_done(){
    {
      std::lock_guard<std::mutex> lock(mutex);
      done = true;
    }
    cv.notify_all();
  }

  std::mutex mutex;
  std::condition_variable cv;
  std::vector< std::unique_ptr<vk::structure::Command> > vec_command;
  VkSemaphore semaphore = VK_NULL_HANDLE;
  bool supress = true;
  bool done = false;

  //---------------------------
};

}
