#pragma once

#include <Utility/Specific/common.h>


namespace prf::vulkan{

struct Thread{
  //---------------------------

  std::thread::id ID;
  std::string name;

  //---------------------------
};

enum Queue_type{
  GRAPHICS = 0,
  PRESENTATION = 1,
  TRANSFER = 2,
};
struct Queue{
  //---------------------------

  int type = -1;
  int ID_family = -1;

  //---------------------------
};

struct Info{
  //---------------------------

  string selected_gpu;

  //---------------------------
};

}
