#pragma once

#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Data/Topology.h>
#include <Utility/Base/Data/Path.h>
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
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec3 centroid = glm::vec3(0.0f, 0.0f, 0.0f);
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
  std::vector<float> Is_cor; //Corrected intensity
  std::vector<float> Is_cal; //Calibrated intensity
  std::vector<float> It; //Incidence angle
  std::vector<float> R; //Range
  std::vector<float> A; //Azimuth
  std::vector<int> idx; //Index

  //---------------------------
};

}