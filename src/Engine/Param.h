#ifndef PARAM_ENGINE_H
#define PARAM_ENGINE_H

#include "ENG_camera/Struct_camera.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param{
  //---------------------------

  int max_fps = 120;
  glm::vec4 background_color = glm::vec4(0.4, 0.4, 0.4, 1);

  Struct_camera camera;

  //---------------------------
};

#endif
