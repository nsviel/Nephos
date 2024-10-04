#pragma once

#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <vulkan/vulkan.h>
#include <condition_variable>
#include <memory>


namespace vk::structure{

struct Command_set{
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
  bool done = false;

  std::vector< std::unique_ptr<vk::structure::Command> > vec_command;
  std::shared_ptr<vk::structure::Fence> fence;

  //---------------------------
};

}
