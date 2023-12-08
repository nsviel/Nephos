#pragma once

#include <UTL_specific/common.h>

class GUI;
class RND_control;
class GUI_image;
class VK_imgui;
class UTL_window;


namespace gui::rnd::panel{

class Engine
{
public:
  //Constructor / Destructor
  Engine(GUI* gui);
  ~Engine();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();
  void engine_control();
  void resize();

private:
  RND_control* gui_control;
  GUI_image* gui_image;
  VK_imgui* vk_imgui;
  UTL_window* utl_window;

  bool has_been_initialized;
};

}
