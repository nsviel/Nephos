#pragma once

#include <Vulkan/Core/VK_pool/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_queue/Manager.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::queue::structure{

struct Queue{
  //---------------------------

  std::vector<vk::pool::structure::Command_buffer*> vec_pool;
  std::string thread_ID;
  vk::queue::Type type;
  VkQueue handle = VK_NULL_HANDLE;
  float priority = 1.0f;
  int family_ID = -1;
  int family_index = 0;

  //---------------------------
};

}
