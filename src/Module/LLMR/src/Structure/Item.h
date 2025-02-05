#pragma once

#include <glm/glm.hpp>
#include <string>


namespace llmr::structure{

struct Item{
  //---------------------------

  std::string prefix = "";
  std::string texte = "";
  glm::vec4 color = glm::vec4(1, 1, 1, 1);

  //---------------------------
};

}
