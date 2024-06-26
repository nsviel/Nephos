#pragma once

#include <Vulkan/VK_struct/Struct_pool.h>
#include <vulkan/vulkan.h>


namespace vk::queue::structure{

struct Queue{
  //---------------------------

  VkQueue handle = VK_NULL_HANDLE;
  float priority = 1.0f;
  int family_ID = -1;
  int family_index = 0;

  vector<vk::pool::Command_buffer*> vec_pool;

  //---------------------------
};

}
