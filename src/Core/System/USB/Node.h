#pragma once

#include <Utility/Base/Class/Node.h>

namespace sys{class Node;}

namespace usb{class Structure;}
namespace usb{class Monitor;}
namespace usb{class Reference;}


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

  inline usb::Structure* get_usb_struct(){return usb_struct;}

private:
  usb::Structure* usb_struct;
  usb::Monitor* usb_monitor;
  usb::Reference* usb_reference;
};

}
