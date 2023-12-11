#pragma once

#include <Utility/UTL_specific/common.h>
#include <GUI/TAB_render/Engine/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>

class GUI;
class VK_imgui;
class UTL_window;


namespace gui::engine{

class Render
{
public:
  //Constructor / Destructor
  Render(GUI* gui);
  ~Render();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();
  void engine_control();
  void resize();

private:
  gui::engine::Control* gui_control;
  gui::media::Image* gui_image;
  VK_imgui* vk_imgui;
  UTL_window* utl_window;

  bool has_been_initialized;
};

}
