#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Engine/Capture/Kinect/Namespace.h>
#include <Engine/Capture/Kinect/Data/Namespace.h>

class GUI;
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

  //Overlay
  void compute_hovered_pixel(eng::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(K4A_device* device, eng::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(K4A_device* device, eng::kinect::structure::Image* image);
  void overlay_pixel(eng::kinect::structure::Image* image, ImVec2 image_size);

private:
  GUI* gui;
  eng::kinect::Kinect* kinect;
  eng::kinect::data::Depth* k4a_depth;
  eng::kinect::data::Infrared* k4a_infrared;
  K4A_swarm* k4a_swarm;

  vector<gui::media::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
};

}
