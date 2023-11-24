#ifndef KINECT_H
#define KINECT_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

#include <UTL_specific/common.h>

class Struct_kinect;
class K4A_configuration;
class K4A_swarm;


class Kinect
{
public:
  //Constructor / Destructor
  Kinect();
  ~Kinect();

public:
  //Main function
  void init();
  void run();

  inline Struct_kinect* get_struct_kinect(){return struct_kinect;}

private:
  Struct_kinect* struct_kinect;
  K4A_configuration* k4a_configuration;
  K4A_swarm* k4a_swarm;
};

#endif
