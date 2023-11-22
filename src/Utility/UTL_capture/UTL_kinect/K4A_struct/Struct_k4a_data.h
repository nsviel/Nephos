#ifndef STRUCT_K4A_DATA_H
#define STRUCT_K4A_DATA_H

#include <k4a/k4a.hpp>
#include <string>


struct K4A_image{
  //---------------------------

  int width;
  int height;
  uint8_t* buffer;
  size_t size;
  std::string format;
  std::chrono::microseconds timestamp;

  //---------------------------
};

struct Struct_k4a_data{
  //---------------------------

  k4a::capture* capture = nullptr;
  K4A_image color;
  K4A_image depth;
  K4A_image ir;
  bool data_ready = false;

  //---------------------------
};



#endif
