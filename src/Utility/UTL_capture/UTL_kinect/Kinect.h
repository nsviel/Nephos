#ifndef KINECT_H
#define KINECT_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>

#include <UTL_specific/common.h>

class Struct_kinect;
class K4A_thread;
class K4A_device;


class Kinect
{
public:
  //Constructor / Destructor
  Kinect();
  ~Kinect();

public:
  //Main function
  void run();
  void loop();

  //Subfunction
  void make_k4a_configuration(Struct_k4a_device* device);
  void start_camera();

  inline K4A_thread* get_k4a_thread(){return k4a_thread;}
  inline K4A_device* get_k4a_device(){return k4a_device;}
  inline Struct_kinect* get_struct_kinect(){return struct_kinect;}

private:
  Struct_kinect* struct_kinect;
  K4A_thread* k4a_thread;
  K4A_device* k4a_device;
};

#endif
