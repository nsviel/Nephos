#ifndef STRUCT_SYNCHRO_H
#define STRUCT_SYNCHRO_H

#include <ELE_specific/common.h>


struct Struct_synchro{
  //---------------------------

  std::vector<VkFence> vec_fence;
  VkFence fence;

  //---------------------------
};

#endif
