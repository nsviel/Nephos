#ifndef K4A_DEVICE_H
#define K4A_DEVICE_H

#include <UTL_specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Struct_kinect;


class K4A_device
{
public:
  //Constructor / Destructor
  K4A_device(Struct_kinect* struct_kinect);
  ~K4A_device();

public:
  //Main function
  void open_selected_device();
  void refresh_device_list();

private:
  Struct_kinect* struct_kinect;

  vector<std::pair<int, string>> connected_device;
  k4a::device selected_device;
  int selected_device_idx = -1;
};

#endif
