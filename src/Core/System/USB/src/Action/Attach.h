#pragma once

#include <libudev.h>
#include <string>

namespace usb{class Node;}
namespace usb{class Structure;}
namespace usb::structure{class Device;}
namespace io::imp{class Importer;}


namespace usb{

class Attach
{
public:
  //Constructor / Destructor
  Attach(usb::Node* node_usb);
  ~Attach();

public:
  //Main function
  void manage_action();

  //Subfunction
  void update_device_map();
  void run_capture();
  
private:
  usb::Structure* usb_struct;
  io::imp::Importer* io_importer;
};

}
