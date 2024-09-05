#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}
namespace io{class Node;}
namespace dat{class Node;}

namespace usb{class Node;}


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

  inline io::Node* get_node_io(){return node_io;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}

private:
  vk::Node* node_vulkan;
  io::Node* node_io;
  dat::Node* node_data;

  usb::Node* node_usb;
};

}
