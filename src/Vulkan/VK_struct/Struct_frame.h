#ifndef STRUCT_FRAME_H
#define STRUCT_FRAME_H

#include <ELE_specific/common.h>
#include <VK_struct/Struct_image.h>


struct Struct_frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_image image;

  //A suprimer !!!
  Struct_image depth;

  //---------------------------
};


#endif
