#pragma once

#include <Utility/Base/Data/Attribut.h>
#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Data/Topology.h>
#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>


namespace utl::base{

struct Data : public utl::base::Element{
  //---------------------------

  //State
  bool is_visible = true;
  int type = utl::element::DATA;
  int nb_data_max = -1;
  int width = -1;
  int height = -1;
  int size = -1;

  //Infos
  utl::base::Topology topology;
  utl::base::Path path;
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec3 centroid = glm::vec3(0.0f, 0.0f, 0.0f);

  //Data
  std::vector<glm::vec3> xyz;   //XYZ location
  std::vector<glm::vec3> rgb;   //RGB color
  std::vector<glm::vec4> rgba;  //Displayed color data
  std::vector<glm::vec3> Nxyz;  //Normal
  std::vector<glm::vec2> uv;    //UV coordinate
  std::vector<utl::base::data::Attribut> vec_attribut;

  std::vector<float> Is; //Intensity
  std::vector<float> Is_cor; //Corrected intensity

  //---------------------------
};

}
