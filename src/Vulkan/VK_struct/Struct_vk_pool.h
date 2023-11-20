#ifndef STRUCT_POOL_H
#define STRUCT_POOL_H

#include <UTL_specific/common.h>


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


#endif
