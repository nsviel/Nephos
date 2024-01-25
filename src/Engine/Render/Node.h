#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Engine;}
namespace eng::renderpass{class Manager;}
namespace eng::shader{class EDL;}
namespace eng::shader{class SCE;}
namespace eng::render::gui{class Shader;}
namespace eng::render::gui{class Renderer;}


namespace eng::render{

class Node
{
public:
  Node(eng::Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline eng::Engine* get_engine(){return engine;}
  inline eng::shader::EDL* get_shader_edl(){return shader_edl;}
  inline eng::shader::SCE* get_shader_scene(){return shader_scene;}

private:
  eng::Engine* engine;
  eng::renderpass::Manager* eng_renderpass;
  eng::shader::EDL* shader_edl;
  eng::shader::SCE* shader_scene;
  eng::render::gui::Shader* gui_shader;
  eng::render::gui::Renderer* gui_render;

  bool show_panel;
};

}
