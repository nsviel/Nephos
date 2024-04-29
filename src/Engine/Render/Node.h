#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace rnd::gui{class Option;}
namespace rnd::gui{class Shader;}
namespace rnd::gui{class Renderer;}
namespace rnd::gui{class Control;}


namespace rnd{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main functions
  void init();
  void gui();

  //Subfunction

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline rnd::gui::Control* get_gui_control(){return gui_control;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  rnd::gui::Control* gui_control;
  rnd::gui::Option* gui_option;
  rnd::gui::Shader* gui_shader;
  rnd::gui::Renderer* gui_render;
};

}
