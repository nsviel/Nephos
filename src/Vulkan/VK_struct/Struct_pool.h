#pragma once

#include <Utility/Specific/common.h>


namespace vk::pool{

struct Command_buffer{
  //---------------------------

  VkCommandPool allocator;
  std::vector<vk::structure::Command_buffer> tank;
  uint32_t size = 100;
  bool is_available = true;
  std::thread::id thread_ID;

  //---------------------------
};

struct Fence{
  //---------------------------

  std::vector<vk::structure::Fence> tank;
  uint32_t size = 100;

  //---------------------------
};

struct Semaphore{
  //---------------------------

  std::vector<vk::structure::Semaphore> tank;
  uint32_t size = 100;

  //---------------------------
};

struct Descriptor{
  //---------------------------

  VkDescriptorPool memory;
  std::vector<vk::structure::Descriptor> tank;
  uint32_t size = 100;

  //---------------------------
};

struct Command{
  //---------------------------

  std::vector<vk::pool::Command_buffer> tank;
  uint32_t size = 10;

  //---------------------------
};

}


namespace vk::structure{

struct Pool{
  //---------------------------

  vk::pool::Command command;
  vk::pool::Fence fence;
  vk::pool::Semaphore semaphore;
  vk::pool::Descriptor descriptor;

  //---------------------------
};

}
