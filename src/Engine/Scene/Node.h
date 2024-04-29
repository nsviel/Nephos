#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace sce{class Init;}
namespace eng{class Node;}
namespace gly{class Node;}
namespace mod{class Node;}


namespace sce{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline gly::Node* get_node_glyph(){return node_glyph;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  gly::Node* node_glyph;

  //Child
  sce::Init* sce_init;
  mod::Node* node_module;

  bool show_scene = true;
  bool show_loader = true;
};

}
