#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::shader{class EDL;}
namespace eng::shader{class SCE;}
namespace eng::render::gui{class Shader;}
namespace eng::render::gui{class Renderer;}


namespace eng::shader{

class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline eng::shader::EDL* get_edl_shader(){return edl_shader;}
  inline eng::shader::SCE* get_sce_shader(){return sce_shader;}

private:
  eng::shader::EDL* edl_shader;
  eng::shader::SCE* sce_shader;
  eng::render::gui::Shader* gui_shader;
  eng::render::gui::Renderer* gui_render;

  bool show_panel;
};

}
