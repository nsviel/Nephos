#pragma once

#include <Utility/Specific/Common.h>
#include <Vulkan/VK_struct/Struct_query.h>
#include <mutex>

namespace vk::structure{struct Query;}
namespace vk::structure{struct Fence;}


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  int UID = 0;

  //Command
  string name = "";
  std::mutex mutex;
  vk::structure::Query query;
  vk::structure::Fence* fence = nullptr;
  VkCommandBuffer handle = VK_NULL_HANDLE;
  float timestamp = 0;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
