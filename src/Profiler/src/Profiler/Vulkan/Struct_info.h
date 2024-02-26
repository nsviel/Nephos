#pragma once

#include <Utility/Specific/common.h>


namespace prf::vulkan{

struct Thread{
  //---------------------------

  std::thread::id ID;
  std::string name; 

  //---------------------------
};

struct Info{
  //---------------------------

  string selected_gpu;

  //---------------------------
};

}
