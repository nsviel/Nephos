#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Data/Namespace.h>
#include <Utility/Base/Namespace.h>

class GUI;


namespace gui::kinect{

class Stream : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Stream(GUI* gui, bool* show_window, string name);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel();

  //All devices
  void vec_device_tab();
  void device_tab(k4n::Device* device);

  //Device capture windows
  void draw_camera_color(k4n::Device* device, ImVec2 image_size);
  void draw_camera_color_from_depth(k4n::Device* k4n_device, ImVec2 image_size);
  void draw_camera_depth(k4n::Device* device, ImVec2 image_size);
  void draw_camera_ir(k4n::Device* device, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(k4n::structure::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(k4n::Device* device, k4n::structure::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(k4n::Device* device, k4n::structure::Image* image);
  void overlay_pixel(k4n::structure::Image* image, ImVec2 image_size);

private:
  GUI* gui;
  k4n::Node* node_kinect;
  k4n::data::Depth* k4a_depth;
  k4n::data::Infrared* k4a_infrared;
  k4n::Swarm* k4a_swarm;

  vector<gui::media::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
};

}
