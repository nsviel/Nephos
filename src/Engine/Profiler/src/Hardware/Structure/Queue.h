#pragma once

#include <string>


namespace prf::hardware::queue{

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

namespace prf::hardware{

struct Queue{
  //---------------------------

  prf::hardware::queue::Type type;
  std::string thread_ID = "";
  int family_ID = -1;
  int number = 0;

  //---------------------------
};

}
