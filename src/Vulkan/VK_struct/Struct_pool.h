#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Pool{
  //---------------------------

  //Command
  VkCommandPool command;
  uint32_t nb_command_buffer = 0;

  //Descriptor
  VkDescriptorPool descriptor;
  uint32_t nb_descriptor_allocated = 0;

  //---------------------------
};

}
