#pragma once

#include <Utility/Specific/Common.h>


namespace prf::vulkan{

struct Queue_family{
  //---------------------------

  int nb_queue = 0;
  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

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


}
