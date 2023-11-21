#ifndef STRUCT_K4A_DATA_H
#define STRUCT_K4A_DATA_H

#include <k4a/k4a.hpp>


struct K4A_image{
  //---------------------------

  uint8_t* buffer;
  int width;
  int height;

  //---------------------------
};

struct Struct_k4a_data{
  //---------------------------

  k4a::capture* capture = nullptr;
  K4A_image color;
  K4A_image depth;
  K4A_image ir;

  //---------------------------
};



#endif
