#ifndef STRUCT_SYNCHRO_H
#define STRUCT_SYNCHRO_H

#include <ELE_specific/common.h>


struct Struct_synchro{
  //---------------------------

  std::vector<VkSemaphore> vec_semaphore_beg;
  std::vector<VkSemaphore> vec_semaphore_end;
  std::vector<VkFence> vec_fence;

  //---------------------------
};

#endif
