#pragma once

#include <Vulkan/VK_struct/Struct_query.h>
#include <Vulkan/VK_synchronization/Structure/Fence.h>
#include <vulkan/vulkan.h>
#include <string>
#include <mutex>


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  int UID = 0;

  //Command
  std::string name = "";
  std::mutex mutex;
  vk::structure::Query query;
  vk::synchro::structure::Fence* fence = nullptr;
  VkCommandBuffer handle = VK_NULL_HANDLE;
  float timestamp = 0;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
