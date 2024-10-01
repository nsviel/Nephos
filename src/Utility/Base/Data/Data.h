#pragma once

#include <Utility/Base/Data/Field.h>
#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Data/Topology.h>
#include <Utility/Base/Data/Path.h>
#include <Utility/Base/Data/Texture.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <list>


namespace utl::base{

struct Data : public utl::base::Element{
  //---------------------------

  Data(){
    this->type = "data";
  }

  //State
  bool is_visible = true;
  bool is_updated = false;
  int size_max = -1;
  int width = -1;
  int height = -1;
  int size = -1;
  std::mutex mutex;

  //Infos
  utl::base::Path path;
  utl::base::Topology topology;
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec3 centroid = glm::vec3(0.0f, 0.0f, 0.0f);

  //Data
  std::vector<glm::vec3> xyz;   //XYZ location
  std::vector<glm::vec3> rgb;   //RGB color
  std::vector<glm::vec4> rgba;  //Displayed color data
  std::vector<glm::vec3> Nxyz;  //Normal
  std::vector<glm::vec2> uv;    //UV coordinate
  std::unordered_map<std::string, std::shared_ptr<utl::base::Field>> map_field;
  std::unordered_map<std::string, std::shared_ptr<utl::base::Image>> map_image;

  //---------------------------
};

}
