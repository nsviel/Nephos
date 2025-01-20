#pragma once

#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>


namespace utl::base{

struct Transformation{
  //---------------------------

  glm::mat4 matrix = glm::mat4(1.0f);
  glm::vec3 coeff = glm::vec3(0.0f);

  //---------------------------
};

struct Pose{
  //---------------------------

  //State
  bool is_movable = true;
  utl::base::Path path;

  //Data
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);

  //Transformation atomic
  utl::base::Transformation translation;
  utl::base::Transformation rotation;
  utl::base::Transformation scale;

  //Transformation matrix
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 initial = glm::mat4(1.0f);

  //---------------------------
};

}
