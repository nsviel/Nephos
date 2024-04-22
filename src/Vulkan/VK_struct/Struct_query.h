#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Query{
  //---------------------------

  VkQueryPool pool = VK_NULL_HANDLE;
  int nb_query = 100;
  bool is_available = true;

  //---------------------------
};

}
