#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Engine/Render/gui/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Engine/Capture/K4N/src/Data/Namespace.h>


class Engine;


namespace eng::k4n::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(eng::k4n::Node* k4n_node, bool* show_window, string name);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel();

  //All devices
  void vec_device_tab();
  void vec_stream_tab(eng::k4n::dev::Sensor* device);

  //Device capture windows
  void draw_camera_color(eng::k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_color_from_depth(eng::k4n::dev::Sensor* k4n_sensor, ImVec2 image_size);
  void draw_camera_depth(eng::k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_ir(eng::k4n::dev::Sensor* device, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(eng::k4n::structure::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(eng::k4n::dev::Sensor* device, eng::k4n::structure::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(eng::k4n::dev::Sensor* device, eng::k4n::structure::Image* image);
  void overlay_pixel(eng::k4n::structure::Image* image, ImVec2 image_size);

  //Subfunction
  ImGuiTabItemFlags get_device_tab_flag(eng::k4n::dev::Sensor* sensor);
  ImGuiTabItemFlags get_sensor_tab_flag(int tab_id);

private:
  eng::k4n::Node* k4a_node;
  eng::k4n::data::Depth* k4a_depth;
  eng::k4n::data::Infrared* k4a_infrared;
  eng::k4n::dev::Swarm* k4n_swarm;

  vector<eng::render::gui::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  string name;
  bool* show_window;
  int current_tab_id = 0;
};

}
