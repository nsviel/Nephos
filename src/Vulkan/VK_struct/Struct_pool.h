#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Pool_command_buffer{
  //---------------------------

  VkCommandPool command;
  uint32_t size = 0;

  //---------------------------
};


struct Pool{
  //---------------------------

  //Command
  Pool_command_buffer command_buffer;

  //Descriptor
  VkDescriptorPool descriptor;
  uint32_t nb_descriptor_allocated = 0;

  //---------------------------
};

}
