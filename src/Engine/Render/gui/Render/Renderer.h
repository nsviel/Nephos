#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Render/gui/Namespace.h>
#include <Engine/Render/gui/Namespace.h>
#include <Utility/GUI/Plot/Namespace.h>
#include <Engine/Camera/gui/Control.h>
#include <Engine/Operation/gui/Namespace.h>

class Engine;
class VK_imgui;
class VK_info;

namespace eng::render::gui{class Control;}


namespace eng::render::gui{

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
  eng::ope::gui::Control* ope_control;
  utl::element::Window* utl_window;
  utl::gui::plot::Profiler* profiler;
  eng::cam::Node* cam_node;
  VK_imgui* vk_imgui;
  VK_info* vk_info;

  bool has_been_initialized;
  bool with_profiler_overlay;
};

}
