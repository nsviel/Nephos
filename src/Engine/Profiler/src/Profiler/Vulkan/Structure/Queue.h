#pragma once


namespace prf::vulkan::queue{

struct Family{
  //---------------------------

  int nb_queue = 0;
  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

  //---------------------------
};

enum Type{
  GRAPHICS = 0,
  PRESENTATION = 1,
  TRANSFER = 2,
};

}

namespace prf::vulkan{

struct Queue{
  //---------------------------

  int number = 0;
  int ID_family = -1;

  //---------------------------
};

}
