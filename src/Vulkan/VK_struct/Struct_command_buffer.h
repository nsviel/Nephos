#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Struct_query.h>

namespace vk::structure{struct Query;}
namespace vk::structure{struct Fence;}


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  int UID = 0;

  //Command
  string name = "";
  vk::structure::Query query;
  vk::structure::Fence* fence;
  VkCommandBuffer command = VK_NULL_HANDLE;
  float timestamp = 0;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
