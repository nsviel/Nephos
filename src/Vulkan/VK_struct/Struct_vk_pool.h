#pragma once

#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_pool{
  //---------------------------

  //Command
  VkCommandPool command;
  uint32_t nb_command_allocated = 0;

  //Descriptor
  VkDescriptorPool descriptor;
  uint32_t nb_descriptor_allocated = 0;

  //---------------------------
};

}
