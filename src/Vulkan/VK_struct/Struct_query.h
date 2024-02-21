#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Query{
  //---------------------------

  VkQueryPool pool;
  int nb_query = 100;

  //---------------------------
};

}
