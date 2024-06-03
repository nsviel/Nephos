#pragma once

#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Topology.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>


namespace utl::base{

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
  std::string format = "";
  glm::vec4 unicolor;
  utl::base::Topology topology;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> rgb;
  std::vector<glm::vec4> rgba; //Displayed color data
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
