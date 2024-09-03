#pragma once

#include <libudev.h>

namespace usb{class Node;}


namespace usb{

class Monitor
{
public:
  //Constructor / Destructor
  Monitor(usb::Node* node_usb);
  ~Monitor();

public:
  //Main function
  void init();
  void usb_monitor();

private:
  usb::Structure* usb_struct;
};

}
