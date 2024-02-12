#pragma once

#include <Utility/Specific/common.h>


namespace vk::pool{

struct Command_buffer{
  //---------------------------

  VkCommandPool memory;
  std::vector<vk::structure::Command_buffer> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Fence{
  //---------------------------

  std::vector<vk::structure::Fence> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Semaphore{
  //---------------------------

  std::vector<vk::structure::Semaphore> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Descriptor{
  //---------------------------

  VkDescriptorPool memory;
  std::vector<vk::structure::Descriptor> pool;
  uint32_t size = 100;

  //---------------------------
};

}


namespace vk::structure{

struct Pool{
  //---------------------------

  std::map<std::string, vk::pool::Command_buffer> command_buffer;
  vk::pool::Fence fence;
  vk::pool::Semaphore semaphore;
  vk::pool::Descriptor descriptor;

  //---------------------------
};

}
