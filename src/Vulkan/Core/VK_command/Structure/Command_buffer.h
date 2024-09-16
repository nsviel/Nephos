#pragma once

#include <Vulkan/Core/VK_pool/Structure/Query.h>
#include <Vulkan/Core/VK_synchronization/Structure/Fence.h>
#include <vulkan/vulkan.h>
#include <string>
#include <mutex>


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  int UID = 0;

  //Addon
  vk::pool::structure::Query query;
  std::string name = "";
  std::mutex mutex;

  //Command
  VkCommandBuffer handle = VK_NULL_HANDLE;
  float duration = 0;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
