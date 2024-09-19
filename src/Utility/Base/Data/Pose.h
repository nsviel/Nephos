#pragma once

#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>


namespace utl::base{

//Generique data structure
struct Pose{
  //---------------------------

  //State
  bool is_movable = true;
  utl::base::Path path;

  //Data
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 root = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);

  //Transformation atomic
  glm::mat4 rotat = glm::mat4(1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);

  //Transformation matrix
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 initial = glm::mat4(1.0f);

  //---------------------------
};

}
