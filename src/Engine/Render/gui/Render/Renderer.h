#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Render/gui/Namespace.h>
#include <Engine/Render/gui/Media/Namespace.h>
#include <Utility/GUI/Plot/Namespace.h>
#include <Engine/Camera/gui/Control.h>

class Engine;
class VK_imgui;
class VK_info;


namespace gui::engine{
class Control;


class Renderer
{
public:
  //Constructor / Destructor
  Renderer(Engine* engine);
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
  //gui::engine::Control* ope_control;
  util::element::Window* utl_window;
  gui::plot::Profiler* profiler;
  camera::gui::Control* cam_control;
  VK_imgui* vk_imgui;
  VK_info* vk_info;

  bool has_been_initialized;
  bool with_profiler_overlay;
};

}
