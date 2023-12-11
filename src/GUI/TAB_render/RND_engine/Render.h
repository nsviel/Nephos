#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/RND_engine/Namespace.h>
#include <GUI_utility/Media_nsp.h>

class GUI;
class VK_imgui;
class UTL_window;


namespace gui::rnd::engine{

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
  gui::rnd::engine::Control* gui_control;
  gui::media::Image* gui_image;
  VK_imgui* vk_imgui;
  UTL_window* utl_window;

  bool has_been_initialized;
};

}
