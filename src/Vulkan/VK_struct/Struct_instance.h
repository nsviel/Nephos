#ifndef STRUCT_INSTANCE_H
#define STRUCT_INSTANCE_H

#include <ELE_specific/common.h>


struct Struct_instance{
  //---------------------------

  VkInstance instance;
  int max_frame_inflight = 2;
  vector<const char*> extension_ext;
  vector<const char*> extension_khr;

  //---------------------------
};


#endif
