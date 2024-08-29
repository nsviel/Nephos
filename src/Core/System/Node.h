#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}

namespace prf{class Node;}


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

  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  vk::Node* node_vulkan;
  
  prf::Node* node_profiler;
};

}
