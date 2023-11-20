#ifndef K4A_CAPTURE_H
#define K4A_CAPTURE_H

#include <UTL_specific/common.h>

class Struct_kinect;
class K4A_thread;
class K4A_device;


class K4A_capture
{
public:
  //Constructor / Destructor
  K4A_capture();
  ~K4A_capture();

public:
  //Main function
  void run();

  //Subfunction
  void make_k4a_configuration();
  void start_camera();

private:
  Struct_kinect* struct_kinect;
  K4A_thread* k4a_thread;
  K4A_device* k4a_device;
};

#endif
