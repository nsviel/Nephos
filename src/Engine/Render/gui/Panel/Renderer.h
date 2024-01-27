#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Imgui;}
namespace vk::main{class Info;}
namespace eng::render{class Node;}
namespace eng::cam{class Node;}
namespace eng::ope::gui{class Control;}
namespace utl::element{class Window;}
namespace utl::gui::plot{class Profiler;}


namespace eng::render::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(eng::render::Node* node_render);
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
  vk::main::Imgui* vk_imgui;
  vk::main::Info* vk_info;

  string name;
  bool has_been_initialized;
  bool with_profiler_overlay;
};

}
