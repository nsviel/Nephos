#pragma once

#include <vulkan/vulkan.h>


namespace vk::pool::structure{

struct Query{
  //---------------------------

  VkQueryPool pool = VK_NULL_HANDLE;
  int nb_query = 100;
  bool is_available = true;

  //---------------------------
};

}
