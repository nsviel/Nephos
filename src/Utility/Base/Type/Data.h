#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>


namespace utl::topology{

enum Type{
  POINT = 0,
  LINE = 1,
  TRIANGLE = 2,
  QUAD = 3,
};

}

namespace utl::type{

struct Topology{
  //---------------------------

  int type = utl::topology::POINT;
  int width = 5;

  //---------------------------
};

struct Data{
  //---------------------------

  //State
  int UID = -1;
  int nb_data_max = -1;
  int width = -1;
  int height = -1;
  int size = -1;
  bool is_visible = true;

  //Infos
  std::string name = "";
  std::string path = "";
  std::string path_save = "";
  std::string path_texture = "";
  std::string file_format = "";
  glm::vec4 unicolor;
  utl::type::Topology topology;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<bool> goodness;
  std::vector<int> idx;
  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;

  //---------------------------
};

}
