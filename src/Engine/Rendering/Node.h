#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace ope{class Node;}
namespace rnd::gui{class Option;}
namespace rnd::gui{class Shader;}
namespace rnd::gui{class Renderer;}


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

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline ope::Node* get_node_operation(){return node_operation;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  ope::Node* node_operation;

  rnd::gui::Option* gui_option;
  rnd::gui::Shader* gui_shader;
  rnd::gui::Renderer* gui_render;
};

}
