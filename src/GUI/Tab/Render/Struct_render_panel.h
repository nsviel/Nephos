#ifndef STRUCT_RENDER_PANEL_H
#define STRUCT_RENDER_PANEL_H

#include <Specific/Struct/struct_object.h>
#include <Specific/Struct/struct_set.h>
#include <string>
#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <iostream>


struct Struct_render_panel{
  //---------------------------

  bool show_camera   = false;
  bool show_object   = false;
  bool show_set      = false;
  bool show_shader   = true;
  bool show_capture  = true;
  bool show_database = false;
  bool show_profiler = true;
  bool show_scene    = true;
  bool show_option   = false;

  //---------------------------
};

#endif
