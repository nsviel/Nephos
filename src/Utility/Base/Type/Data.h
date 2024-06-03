#pragma once

#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Topology.h>
#include <Utility/Base/Type/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::base{

struct Data : public utl::base::Element{
  //---------------------------

  Data(){
    this->type = utl::element::DATA;
  }

  //State
  int nb_data_max = -1;
  int width = -1;
  int height = -1;
  int size = -1;
  bool is_visible = true;

  //Infos
  std::string format = "";
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  utl::base::Topology topology;
  utl::base::Path path;

  //Data
  std::vector<glm::vec3> xyz; //XYZ location
  std::vector<glm::vec3> rgb; //RGB color
  std::vector<glm::vec4> rgba; //Displayed color data
  std::vector<glm::vec3> Nxyz; //Normal
  std::vector<glm::vec2> uv;  //UV coordinate
  std::vector<float> ts; //Timestamp
  std::vector<float> Is; //Intensity
  std::vector<float> R; //Range
  std::vector<float> A; //Azimuth
  std::vector<int> idx; //Index

  //---------------------------
};

}
