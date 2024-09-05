#pragma once

#include <libudev.h>
#include <string>

namespace usb{class Node;}
namespace usb{class Structure;}
namespace usb{class Attach;}
namespace usb{class Detach;}


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
  void manage_init_state();
  void manage_event();

private:
  usb::Structure* usb_struct;
  usb::Attach* usb_attach;
  usb::Detach* usb_detach;
};

}
