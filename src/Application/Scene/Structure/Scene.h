#pragma once

#include <glm/glm.hpp>
#include <string>


namespace sce::structure{

struct Object{
  //---------------------------

  std::string name = "";
  glm::vec3 position = glm::vec3(0, 0, 0);
  glm::vec3 rotation = glm::vec3(0, 0, 0);
  glm::vec3 scale = glm::vec3(0, 0, 0);

  //---------------------------
};

struct Set{
  //---------------------------

  std::vector<sce::structure::Set> vec_set;
  std::vector<sce::structure::Object> vec_object;

  //---------------------------
};

struct Scene{
  //---------------------------

  std::string name = "";
  std::vector<sce::structure::Set> vec_set;

  //---------------------------
};

}
