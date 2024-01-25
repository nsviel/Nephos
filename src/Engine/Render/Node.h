#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::renderpass{class Manager;}
namespace eng::shader{class EDL;}
namespace eng::shader{class SCE;}
namespace eng::render::gui{class Shader;}
namespace eng::render::gui{class Renderer;}


namespace eng::render{

class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline Engine* get_engine(){return engine;}
  inline eng::shader::EDL* get_edl_shader(){return edl_shader;}
  inline eng::shader::SCE* get_sce_shader(){return sce_shader;}

private:
  Engine* engine;
  eng::renderpass::Manager* eng_renderpass;
  eng::shader::EDL* edl_shader;
  eng::shader::SCE* sce_shader;
  eng::render::gui::Shader* gui_shader;
  eng::render::gui::Renderer* gui_render;

  bool show_panel;
};

}
