#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::dev{class Master;}
namespace eng::render::gui{class Stream;}
namespace eng::k4n::structure{class Data;}


namespace eng::k4n::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(eng::k4n::Node* node_k4n, bool* show_window);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel(eng::k4n::dev::Master* master);

  //All devices
  void vec_device_tab(eng::k4n::dev::Master* master);
  void vec_stream_tab(eng::k4n::dev::Sensor* device);

  //Device capture windows
  void draw_camera_color(eng::k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_depth(eng::k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_ir(eng::k4n::dev::Sensor* device, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(eng::k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(eng::k4n::dev::Sensor* device, eng::k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(eng::k4n::dev::Sensor* device, eng::k4n::structure::Data* image);
  void overlay_pixel(eng::k4n::structure::Data* image, ImVec2 image_size);

private:
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;

  vector<eng::render::gui::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  string name;
  bool* show_window;
  int current_tab_id = 0;
};

}
