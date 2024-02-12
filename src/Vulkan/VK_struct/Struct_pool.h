#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Pool_command_buffer{
  //---------------------------

  VkCommandPool memory;
  std::vector<vk::structure::Command_buffer> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Pool_fence{
  //---------------------------

  std::vector<vk::structure::Fence> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Pool_semaphore{
  //---------------------------

  std::vector<vk::structure::Semaphore> pool;
  uint32_t size = 100;

  //---------------------------
};

struct Pool_descriptor{
  //---------------------------

  VkDescriptorPool memory;
  std::vector<vk::structure::Descriptor> pool;
  uint32_t size = 100;

  //---------------------------
};


struct Pool{
  //---------------------------

  std::map<std::string, vk::structure::Pool_command_buffer> command_buffer;
  Pool_fence fence;
  Pool_semaphore semaphore;
  Pool_descriptor descriptor;

  //---------------------------
};

}
