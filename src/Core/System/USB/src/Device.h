#pragma once

#include <libudev.h>

namespace usb{class Node;}
namespace usb{class Structure;}


namespace usb{

class Device
{
public:
  //Constructor / Destructor
  Device(usb::Node* node_usb);
  ~Device();

public:
  //Main function
  void init();

private:
  usb::Structure* usb_struct;
};

}
