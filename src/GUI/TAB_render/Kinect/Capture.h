#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/Kinect/Namespace.h>

class GUI;
class K4A_depth;
class K4A_infrared;
class K4A_swarm;


namespace gui::kinect{

class Capture : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Capture(GUI* gui, bool* show_window, string name);
  ~Capture();

  //Main function
  void design_panel();

  //All devices
  void vec_device_tab();
  void device_tab(K4A_device* device);

  //Device capture windows
  void draw_camera_color(K4A_device* device, ImVec2 image_size);
  void draw_camera_depth(K4A_device* device, ImVec2 image_size);
  void draw_camera_ir(K4A_device* device, ImVec2 image_size);
  void hovered_info_panel(K4A_image* image);

private:
  GUI* gui;
  util::kinect::Kinect* kinect;
  K4A_depth* k4a_depth;
  K4A_infrared* k4a_infrared;
  K4A_swarm* k4a_swarm;

  vector<gui::media::Stream*> vec_gui_stream;
};

}
