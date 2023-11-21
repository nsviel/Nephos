#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include <string>


struct Struct_image{
  //---------------------------

  int channel;
  int width;
  int height;
  uint8_t* buffer;
  std::string format;

  //---------------------------
};


#endif
