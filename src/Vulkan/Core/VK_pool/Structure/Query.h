#pragma once

#include <vulkan/vulkan.h>


namespace vk::pool::structure{

struct Query{
  //---------------------------

  VkQueryPool pool = VK_NULL_HANDLE;
  bool is_available = true;
  int nb_query = 100;

  //---------------------------
};

}
