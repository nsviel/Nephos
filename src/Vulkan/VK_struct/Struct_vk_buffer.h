#ifndef STRUCT_BUFFER_H
#define STRUCT_BUFFER_H

#include <UTL_specific/common.h>


struct Struct_vk_buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;

  //---------------------------
};


#endif
