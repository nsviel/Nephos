#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include "struct_image.h"
#include "struct_buffer.h"
#include "struct_binding.h"
#include <Specific/common.h>


struct Struct_texture{
  //---------------------------

  Struct_descriptor image;
  Struct_image image;
  Struct_buffer buffer;

  MyTextureData() { memset(this, 0, sizeof(*this)); }

  //---------------------------
};

#endif
