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


namespace utl::type{

struct Vertice{
  //---------------------------

  int size = -1;
  int width = 5;

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

struct Data{
  //---------------------------

  //State
  int UID = -1;
  int nb_data_max = -1;
  int width = -1;
  int height = -1;

  //Infos
  std::string name = "";
  std::string path_data = "";
  std::string path_save = "";
  std::string path_texture = "";
  std::string file_format = "";
  std::string draw_type_name = "";
  glm::vec4 unicolor;

  //Data
  bool has_color;
  bool has_intensity;
  bool has_normal;
  bool has_texture;
  bool has_timestamp;
  bool is_visible = true;

  Vertice point;
  Vertice line;
  Vertice triangle;

  //---------------------------
};

}
