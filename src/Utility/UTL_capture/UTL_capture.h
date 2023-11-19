#ifndef UTL_CAPTURE_H
#define UTL_CAPTURE_H

#include <UTL_specific/common.h>
#include <libusb-1.0/libusb.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>


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
  void open_selected_device();
  void refresh_device_list();
  bool start_camera();

private:
  vector<std::pair<int, string>> connected_device;
  k4a::device selected_device;
  int selected_device_idx = -1;
  bool camera_started;
};

#endif
