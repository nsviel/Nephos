#pragma once

#include <libudev.h>

namespace usb{class Node;}
namespace usb{class Structure;}


namespace usb{

class Reference
{
public:
  //Constructor / Destructor
  Reference(usb::Node* node_usb);
  ~Reference();

public:
  //Main function
  void init();

private:
  usb::Structure* usb_struct;
};

}
