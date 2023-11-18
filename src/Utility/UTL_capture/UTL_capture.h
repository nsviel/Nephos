#ifndef UTL_CAPTURE_H
#define UTL_CAPTURE_H

#include <UTL_specific/common.h>
#include <k4a/k4a/k4a.h>
#include <k4a/k4a/k4atypes.h>
#include <k4a/k4ainternal/capture.h>
#include <k4a/k4ainternal/image.h>
#include <libusb-1.0/libusb.h>


class UTL_capture
{
public:
  //Constructor / Destructor
  UTL_capture();
  ~UTL_capture();

public:
  //Main function
  void truc();

private:
};

#endif
