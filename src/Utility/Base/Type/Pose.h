#pragma once

#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Type/Path.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>


namespace utl::base{

//Generique data structure
struct Pose{
  //---------------------------

  //State
  bool movable = true;
  utl::base::Path path;

  //Data
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 root = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);
  glm::mat4 rotat = glm::mat4(1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 model_init = glm::mat4(1.0f);
  glm::mat4 mvp = glm::mat4(1.0f);

  //---------------------------
};

}
