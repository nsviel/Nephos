#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::media{

//Generique structure to parse data file
struct File{
  //---------------------------

  //Info
  int nb_element;
  std::string name;
  std::string path_data;
  std::string path_transfo;
  std::string path_texture;
  std::string draw_type_name;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec2> uv;

  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;
  std::vector<float> A;

  std::vector<File*> vec_data;

  //---------------------------
};

}
