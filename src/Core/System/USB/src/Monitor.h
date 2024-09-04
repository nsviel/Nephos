#pragma once

#include <libudev.h>

namespace usb{class Node;}
namespace usb{class Structure;}


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
  void manage_action(const std::string& action, const std::string& product);

private:
  usb::Structure* usb_struct;
};

}
