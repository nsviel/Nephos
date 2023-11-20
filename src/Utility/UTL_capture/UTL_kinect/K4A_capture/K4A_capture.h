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
  void start_camera();

  inline K4A_thread* get_k4a_thread(){return k4a_thread;}
  inline K4A_device* get_k4a_device(){return k4a_device;}

private:
  Struct_kinect* struct_kinect;
  K4A_thread* k4a_thread;
  K4A_device* k4a_device;
};

#endif
