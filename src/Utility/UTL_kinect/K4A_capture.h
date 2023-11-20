#ifndef K4A_CAPTURE_H
#define K4A_CAPTURE_H

#include <UTL_specific/common.h>
#include <UTL_kinect/Struct_kinect_config.h>
#include <libusb-1.0/libusb.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>


class K4A_capture
{
public:
  //Constructor / Destructor
  K4A_capture();
  ~K4A_capture();

public:
  //Main function
  void truc();

  //Subfunction
  void machin();
  void chose();
  void open_selected_device();
  void refresh_device_list();
  bool start_camera();
  void make_k4a_configuration(Struct_kinect_config* config);

private:
  Struct_kinect_config* device_config;

  //std::unique_ptr<K4APollingThread> thread_camera_polling;
  //K4ADataSource<k4a::capture> camera_data_source;
  vector<std::pair<int, string>> connected_device;
  k4a::device selected_device;
  int selected_device_idx = -1;
  bool camera_started;
  bool camera_pause;
};

#endif
