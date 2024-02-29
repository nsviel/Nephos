#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::file{

enum Type{
  ENTITY = 0,
  SET = 1,
};


struct Data{
  //---------------------------

  int type = utl::file::ENTITY;
  std::string name = "";
  std::string path = "";

  virtual void hello(){}

  //---------------------------
};

struct Entity : public utl::file::Data{
  //---------------------------

  //Info
  int nb_element = 0;
  int draw_type = utl::topology::POINT;

  std::string path_transfo = "";
  std::string path_texture = "";

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec2> uv;

  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;
  std::vector<float> A;

  //---------------------------
};

struct Set : public utl::file::Data{
  //---------------------------

  std::vector<utl::file::Entity*> vec_data;

  //---------------------------
};

}
