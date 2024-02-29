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

  utl::type::Vertice* get_vertice(){
    utl::type::Vertice* vertice = nullptr;
    switch(draw_type){
      case utl::topology::POINT:{
        vertice = &point;
        break;
      }
      case utl::topology::LINE:{
        vertice = &line;
        break;
      }
      case utl::topology::TRIANGLE:{
        vertice = &triangle;
        break;
      }
    }
    return vertice;
  }

  //State
  int UID = -1;
  int nb_data_max = -1;
  int draw_type = utl::topology::POINT;
  int width = -1;
  int height = -1;

  //Infos
  std::string name = "";
  std::string path = "";
  std::string path_save = "";
  std::string path_texture = "";
  std::string file_format = "";
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
