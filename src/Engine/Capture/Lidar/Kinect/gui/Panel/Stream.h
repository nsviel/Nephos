#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Master;}
namespace eng::gui{class Stream;}
namespace k4n::structure{class Data;}
namespace eng::scene{class Set;}


namespace k4n::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(k4n::Node* node_k4n, bool* show_window);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //All devices
  void vec_device_tab(k4n::dev::Master* master);
  void vec_stream_tab(k4n::dev::Sensor* device);

  //Device capture windows
  void draw_camera_color(k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_depth(k4n::dev::Sensor* device, ImVec2 image_size);
  void draw_camera_ir(k4n::dev::Sensor* device, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(k4n::dev::Sensor* device, k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(k4n::dev::Sensor* device, k4n::structure::Data* image);
  void overlay_pixel(k4n::structure::Data* image, ImVec2 image_size);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
  eng::scene::Set* sce_set;

  vector<eng::gui::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  string name;
  bool* show_window;
  int current_tab_id = 0;
};

}
