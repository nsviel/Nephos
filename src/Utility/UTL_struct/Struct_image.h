#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include <string>


struct Struct_image{
  //---------------------------

  int channel_nb = 4;
  int channel_byte = 1;
  int width;
  int height;
  uint8_t* buffer;
  std::string format;

  //---------------------------
};


#endif
