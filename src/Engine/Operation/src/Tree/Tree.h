#pragma once

#include <Utility/Specific/Common.h>


namespace ope::tree{

struct Cube{
  int level;
  Cube* child[8];

  vec3 min;
  vec3 max;
  vec3 center;

  vector<int> idx_cube;
  vector<int> idx_child;
};

struct Root{
  Cube* child;

  vector<vec3>* xyz_subset;
  vector<vec3> xyz;
  vector<vec4> rgb;
  vector<vec4> level_rgb;
};

}
