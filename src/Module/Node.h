#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace vk{class Node;}
namespace core{class Node;}

namespace rad{class Node;}
namespace llmr{class Node;}


namespace mod{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline rad::Node* get_node_radio(){return node_radio;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;

  //Child
  rad::Node* node_radio;
  llmr::Node* node_llmr;
};

}
