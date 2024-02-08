#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Fence{
  //---------------------------

  VkFence fence;
  bool is_available = true;

  //---------------------------
};

}
