#pragma once

#include <glm/glm.hpp>
#include <string>


struct Configuration{
  //---------------------------

  std::string window_title = "Nephos";
  glm::vec2 window_dim =  glm::vec2(1024, 500);
  glm::vec2 window_dim_min = glm::vec2(500, 250);
  bool run_app = true;

  //---------------------------
};
