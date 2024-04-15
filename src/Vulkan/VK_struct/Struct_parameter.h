#pragma once



#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


namespace vk::structure{

struct Parameter{
  //---------------------------

  //Configuration stuff
  bool headless = false;
  bool dedicated_gpu = true;
  bool* app_running = nullptr;
  glm::vec4 background_color = glm::vec4(0.4f, 0.4f, 0.4f, 1);
  glm::vec2 headless_dim =  glm::vec2(1024, 500);

  //Linked entity
  utl::entity::Camera camera;

  //---------------------------
};

}
