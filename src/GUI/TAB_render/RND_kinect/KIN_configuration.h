#ifndef KIN_CONFIGURATION_H
#define KIN_CONFIGURATION_H

#include <UTL_specific/common.h>

class GUI;
class Kinect;
class K4A_swarm;


class KIN_configuration
{
public:
  //Constructor / Destructor
  KIN_configuration(Kinect* kinect);
  ~KIN_configuration();

  //Main function
  void kinect_configuration();

  //Subfunction
  void kinect_devices();
  void configuration_device();
  void configuration_depth();
  void configuration_color();
  void configuration_general();
  void firmware_info();

private:
  Kinect* kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

#endif
