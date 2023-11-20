#ifndef UTL_CAPTURE_H
#define UTL_CAPTURE_H

#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_capture.h>

class K4A_capture;


class UTL_capture
{
public:
  //Constructor / Destructor
  UTL_capture();
  ~UTL_capture();

public:
  //Main function
  void truc();

  //Subfunction
  void machin();
  void chose();

private:
  K4A_capture* k4a_capture;
};

#endif
