#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace ctr{class Node;}
namespace rnd{class Shader;}
namespace rnd::gui{class Option;}
namespace rnd::gui{class Shader;}
namespace rnd::gui{class Renderer;}


namespace thr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  //Subfunction
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline ctr::Node* get_node_control(){return node_control;}
  inline rnd::Shader* get_rnd_shader(){return rnd_shader;}

private:
  vk::Node* node_vulkan;
  ctr::Node* node_control;

  rnd::Shader* rnd_shader;
  rnd::gui::Option* gui_option;
  rnd::gui::Shader* gui_shader;
  rnd::gui::Renderer* gui_render;

};

}
