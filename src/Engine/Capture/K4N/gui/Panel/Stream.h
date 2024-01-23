#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Media/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Engine/Capture/K4N/src/Data/Namespace.h>


class Engine;


namespace gui::kinect{

class Stream
{
public:
  //Constructor / Destructor
  Stream(Engine* engine, bool* show_window, string name);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel();

  //All devices
  void vec_device_tab();
  void device_tab(k4n::src::dev::Sensor* device);

  //Device capture windows
  void draw_camera_color(k4n::src::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_color_from_depth(k4n::src::dev::Sensor* k4n_sensor, ImVec2 image_size);
  void draw_camera_depth(k4n::src::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_ir(k4n::src::dev::Sensor* device, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(k4n::src::str::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(k4n::src::dev::Sensor* device, k4n::src::str::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(k4n::src::dev::Sensor* device, k4n::src::str::Image* image);
  void overlay_pixel(k4n::src::str::Image* image, ImVec2 image_size);

private:
  GUI* gui;
  k4n::Node* node_kinect;
  k4n::src::data::Depth* k4a_depth;
  k4n::src::data::Infrared* k4a_infrared;
  k4n::src::dev::Swarm* k4n_swarm;

  vector<gui::media::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  bool* show_window;
  string name;
};

}
