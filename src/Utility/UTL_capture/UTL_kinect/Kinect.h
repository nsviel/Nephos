#ifndef KINECT_H
#define KINECT_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

#include <UTL_specific/common.h>

class Struct_kinect;
class K4A_device;
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

  //Subfunction
  void make_k4a_configuration(K4A_device* device);

  inline K4A_device* get_k4a_device(){return k4a_device;}
  inline Struct_kinect* get_struct_kinect(){return struct_kinect;}

private:
  Struct_kinect* struct_kinect;
  K4A_device* k4a_device;
  K4A_swarm* k4a_swarm;
};

#endif
