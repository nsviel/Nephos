#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include <ELE_specific/common.h>
#include "Struct_image.h"


struct Frame{
  //---------------------------

  int ID;

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_image color;
  Struct_image location;
  Struct_image normal;
  Struct_image depth;

  //---------------------------
};


#endif
