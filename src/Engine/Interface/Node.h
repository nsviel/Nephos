#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace itf{class Structure;}
namespace itf::gui{class Option;}
namespace itf::gui{class Shader;}
namespace itf::gui{class Renderer;}


namespace itf{

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
  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline itf::Structure* get_itf_struct(){return itf_struct;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  itf::Structure* itf_struct;
  itf::gui::Option* gui_option;
  itf::gui::Shader* gui_shader;
  itf::gui::Renderer* gui_render;
};

}
