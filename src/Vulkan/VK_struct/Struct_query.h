#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Query{
  //---------------------------

  VkQueryPool pool = VK_NULL_HANDLE;
  int nb_query = 100;
  bool is_in_use = false;

  //---------------------------
};

}
