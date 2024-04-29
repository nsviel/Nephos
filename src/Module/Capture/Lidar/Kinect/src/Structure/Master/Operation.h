#pragma once

#include <Utility/Specific/Common.h>
#include <Operation/Namespace.h>
#include <cstdint>


namespace k4n::transformation{

enum Mode{
  DEPTH_TO_COLOR = 0,
  COLOR_TO_DEPTH = 1,
};

}

namespace k4n::structure{

struct Operation{
  //Processing parameters structure
  //---------------------------

  //Color / Depth transformation
  int transformation_mode = k4n::transformation::COLOR_TO_DEPTH;

  //Colorization
  int fps = 30;
  int color_mode = ope::color::CAMERA;
  int heatmap_mode = ope::color::heatmap::INTENSITY;
  int intensity_diviser = 1000;
  glm::vec2 range_height = glm::vec2(-1, 1);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);

  //Voxelization
  bool voxel = false;
  float voxel_size = 0.25;
  int voxel_min_point = 100;

  //Normal
  bool normal = false;
  bool normal_visible = false;
  int normal_knn = 2;

  //Export
  bool record = false;

  //Triangulation
  bool triangulation = false;

  //---------------------------
};

}