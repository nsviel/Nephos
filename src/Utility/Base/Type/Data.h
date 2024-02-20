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

//Generique data structure
struct Data{
  //---------------------------

  //State
  int UID = -1;
  int nb_point = -1;
  int nb_data_max = -1;
  int draw_line_width = 1;
  int draw_point_size = 5;
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

  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<bool> goodness;
  std::vector<int> idx;
  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;
  std::mutex mutex;

  //---------------------------
};

}
