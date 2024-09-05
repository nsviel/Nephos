#pragma once

#include <libudev.h>
#include <string>

namespace usb{class Node;}
namespace usb{class Structure;}
namespace usb::structure{class Device;}


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
  void loop();
  void close();

  //Subfunction
  void manage_event();
  void manage_plug();
  void manage_unplug();

private:
  usb::Structure* usb_struct;
};

}
