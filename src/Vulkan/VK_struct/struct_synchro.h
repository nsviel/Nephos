#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include <ELE_specific/common.h>


struct Struct_synchro{
  //---------------------------

  std::vector<VkSemaphore> vec_semaphore_beg;
  std::vector<VkSemaphore> vec_semaphore_end;
  std::vector<VkFence> vec_fence;

  //---------------------------
};

#endif
