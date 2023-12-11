#pragma once

#include <ENG_camera/Struct_camera.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


namespace vk::structure{

struct Parameter{
  //---------------------------

  int max_fps = 120;
  bool headless = false;
  bool dedicated_gpu = false;
  glm::vec4 background_color = glm::vec4(0.4, 0.4, 0.4, 1);
  glm::vec2 headless_dim =  glm::vec2(1024, 500);

  Struct_camera camera;

  //---------------------------
};

}
