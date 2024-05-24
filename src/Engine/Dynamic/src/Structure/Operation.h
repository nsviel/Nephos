#pragma once

#include <Utility/Specific/Common.h>
#include <Operation/Namespace.h>
#include <cstdint>


namespace dyn::operation{

struct Structure{
  //---------------------------

  //Voxelization
  bool voxel = false;
  float voxel_size = 0.25;
  int voxel_min_point = 100;

  //Normal
  bool normal = false;
  bool normal_visible = false;
  int normal_knn = 2;

  //Triangulation
  bool triangulation = false;

  //---------------------------
};

}
