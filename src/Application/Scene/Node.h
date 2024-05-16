#pragma once

#include <Utility/Base/Type/Node.h>

namespace app{class Node;}
namespace vk{class Node;}
namespace sce{class Init;}
namespace mod{class Node;}
namespace eng{class Node;}


namespace sce{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  mod::Node* node_module;

  //Child
  sce::Init* sce_init;

  bool show_scene = true;
  bool show_loader = true;
};

}
