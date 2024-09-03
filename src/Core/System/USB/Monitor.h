#pragma once

#include <libudev.h>


namespace sys{

class Monitor
{
public:
  //Constructor / Destructor
  Monitor();
  ~Monitor();

public:
  //Main function
  void usb_monitor();

private:

};

}
