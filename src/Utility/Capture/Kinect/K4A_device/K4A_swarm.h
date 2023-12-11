#pragma once

#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/Kinect/Structure/Namespace.h>
#include <Utility/Capture/Kinect/K4A_device/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>


class K4A_swarm
{
public:
  //Constructor / Destructor
  K4A_swarm(util::kinect::structure::Swarm* struct_k4a_swarm);
  ~K4A_swarm();

public:
  //Main function
  K4A_device* create_device_virtual(string path);
  K4A_device* create_device_real(int index);
  void delete_device(K4A_device* device);
  void refresh_connected_device_list();

private:
  util::kinect::structure::Swarm* struct_k4a_swarm;
  util::kinect::device::Configuration* k4a_configuration;

  int ID_virtual = 0;
  int nb_connected_device = -1;
};
