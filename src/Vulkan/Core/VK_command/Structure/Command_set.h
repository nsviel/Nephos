#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <vulkan/vulkan.h>
#include <condition_variable>
#include <memory>


namespace vk::structure{

struct Command_set{
  //---------------------------

  //Stuff for knowing when command bundle has finished submission
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
  bool presentation = false;
  std::shared_ptr<vk::structure::Semaphore> semaphore;

  //Bundle of commands
  std::vector< std::unique_ptr<vk::structure::Command> > vec_command;

  //---------------------------
};

}
