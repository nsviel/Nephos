#pragma once

#include <Utility/Specific/Common.h>
#include <Operation/Namespace.h>
#include <cstdint>


namespace dyn::operation{

struct Structure{
  //Processing parameters structure
  //---------------------------

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

  //Triangulation
  bool triangulation = false;

  //---------------------------
};

}
