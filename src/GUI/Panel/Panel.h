#ifndef GUI_PARAM_H
#define GUI_PARAM_H

#include <Specific/Struct/struct_object.h>
#include <Specific/Struct/struct_set.h>
#include <string>
#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <iostream>


struct Panel{
  //---------------------------

  bool show_camera   = false;
  bool show_object   = false;
  bool show_set      = false;
  bool show_shader   = false;
  bool show_capture  = true;
  bool show_database = false;
  bool show_profiler = true;
  bool show_scene    = true;

  //---------------------------
};

#endif
