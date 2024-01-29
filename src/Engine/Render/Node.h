#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::renderpass{class Manager;}
namespace eng::render{class Profiler;}
namespace eng::shader{class EDL;}
namespace eng::shader{class SCE;}
namespace eng::render::gui{class Shader;}
namespace eng::render::gui{class Renderer;}
namespace eng::render::gui{class Profiler;}


namespace eng::render{

class Node
{
public:
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline eng::Node* get_engine(){return engine;}
  inline eng::shader::EDL* get_shader_edl(){return shader_edl;}
  inline eng::shader::SCE* get_shader_scene(){return shader_scene;}

private:
  eng::Node* engine;
  eng::renderpass::Manager* eng_renderpass;
  eng::render::Profiler* cpu_profiler;
  eng::render::Profiler* gpu_profiler;
  eng::shader::EDL* shader_edl;
  eng::shader::SCE* shader_scene;
  eng::render::gui::Shader* gui_shader;
  eng::render::gui::Renderer* gui_render;
  eng::render::gui::Profiler* gui_profiler;

  bool show_shader;
  bool show_profiler;
};

}
