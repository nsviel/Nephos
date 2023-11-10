#ifndef STRUCT_INSTANCE_H
#define STRUCT_INSTANCE_H

#include <ELE_specific/common.h>


struct Struct_instance{
  //---------------------------

  int max_frame_inflight = 2;
  VkInstance instance;
  vector<const char*> extension;

  //---------------------------
};


#endif
