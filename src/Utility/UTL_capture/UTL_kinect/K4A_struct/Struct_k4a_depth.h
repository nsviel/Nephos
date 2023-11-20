#ifndef STRUCT_K4A_DEPTH_H
#define STRUCT_K4A_DEPTH_H

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_depth{
  //---------------------------

  bool enabled = true;
  k4a_depth_mode_t mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  k4a::capture* capture = nullptr;
  k4a::device* device = nullptr;

  //---------------------------
};



#endif
