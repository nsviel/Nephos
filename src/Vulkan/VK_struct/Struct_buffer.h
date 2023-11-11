#ifndef STRUCT_BUFFER_H
#define STRUCT_BUFFER_H

#include <ELE_specific/common.h>


struct Struct_buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;

  //---------------------------
};


#endif
