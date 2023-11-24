#ifndef K4A_SWARM_H
#define K4A_SWARM_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

#include <UTL_specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Struct_k4a_swarm;
class K4A_configuration;


class K4A_swarm
{
public:
  //Constructor / Destructor
  K4A_swarm(Struct_k4a_swarm* struct_k4a_swarm);
  ~K4A_swarm();

public:
  //Main function
  K4A_device* create_virtual_device(string path);
  void refresh_connected_device_list();

private:
  Struct_k4a_swarm* struct_k4a_swarm;
  K4A_configuration* k4a_configuration;
};

#endif
