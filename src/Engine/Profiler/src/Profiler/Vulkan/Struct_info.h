#pragma once

#include <Utility/Specific/Common.h>


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

  int number = 0;
  int ID_family = -1;

  //---------------------------
};

struct Info{
  //---------------------------

  string selected_gpu;

  //---------------------------
};

}
