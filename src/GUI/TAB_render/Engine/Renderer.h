#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Engine/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>
#include <GUI/GUI_utility/Plot/Namespace.h>

class GUI;
class VK_imgui;


namespace gui::engine{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(GUI* gui);
  ~Renderer();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_texture();
  void engine_control();
  void engine_overlay(ImVec2 image_pose);
  void resize();

private:
  gui::engine::Control* gui_control;
  gui::media::Image* gui_image;
  util::element::Window* utl_window;
  gui::plot::Profiler* profiler;
  VK_imgui* vk_imgui;
  VK_info* vk_info;

  bool has_been_initialized;
  bool with_profiler_overlay;
};

}
