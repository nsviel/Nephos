#pragma once

#include <libudev.h>
#include <string>

namespace usb{class Node;}
namespace usb{class Structure;}
namespace usb::structure{class Device;}
namespace dat::gph{class Element;}


namespace usb{

class Detach
{
public:
  //Constructor / Destructor
  Detach(usb::Node* node_usb);
  ~Detach();

public:
  //Main function
  void manage_action();

private:
  usb::Structure* usb_struct;
  dat::gph::Element* dat_element;
};

}
