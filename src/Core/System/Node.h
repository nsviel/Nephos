#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}



namespace sys{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}



private:
  vk::Node* node_vulkan;


};

}
