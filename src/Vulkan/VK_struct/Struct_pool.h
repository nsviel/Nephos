#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Pool_command_buffer{
  //---------------------------

  VkCommandPool command;
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


struct Pool{
  //---------------------------

  //Command
  Pool_command_buffer command_buffer;
  Pool_fence fence;

  //Descriptor
  VkDescriptorPool descriptor;
  uint32_t nb_descriptor_allocated = 0;

  //---------------------------
};

}
