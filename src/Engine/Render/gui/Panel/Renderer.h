#pragma once

#include <Utility/Specific/common.h>

class Engine;
class VK_imgui;
class VK_info;
namespace eng::cam{class Node;}
namespace eng::ope::gui{class Control;}
namespace utl::element{class Window;}
namespace utl::gui::plot{class Profiler;}


namespace eng::render::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(Engine* engine);
  ~Renderer();

public:
  //Main functions
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void engine_overlay(ImVec2 image_pose);
  void resize();

private:
  eng::cam::Node* node_camera;
  eng::ope::gui::Control* ope_control;
  utl::element::Window* utl_window;
  utl::gui::plot::Profiler* profiler;
  VK_imgui* vk_imgui;
  VK_info* vk_info;

  string name;
  bool has_been_initialized;
  bool with_profiler_overlay;
};

}
