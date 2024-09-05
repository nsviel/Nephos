#pragma once

#include <Utility/Base/Class/Node.h>

namespace sys{class Node;}
namespace io{class Node;}

namespace usb{class Structure;}
namespace usb{class Monitor;}


namespace usb{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(sys::Node* node_system);
  ~Node();

public:
  //Main function
  void init();

  inline io::Node* get_node_io(){return node_io;}
  
  inline usb::Structure* get_usb_struct(){return usb_struct;}

private:
  io::Node* node_io;

  usb::Structure* usb_struct;
  usb::Monitor* usb_monitor;
};

}
