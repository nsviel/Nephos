#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Graph;}
namespace eng{class Node;}
namespace dat{class Set;}
namespace gui::element{class Stream;}
namespace gui_element = gui::element;
namespace utl::type{class Element;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dyn::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(dyn::Node* node_dynamic, bool* show_window);
  ~Stream();

  //Main function
  void run_panel();
  void design_panel(utl::type::Element* element);

  //All devices
  void vec_device_tab(dat::base::Set* set);
  void vec_stream_tab(dat::base::Entity* entity);

  //Device capture windows
  void draw_camera_color(dat::base::Entity* entity, ImVec2 image_size);
  void draw_camera_depth(dat::base::Entity* entity, ImVec2 image_size);
  void draw_camera_ir(dat::base::Entity* entity, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(dat::base::Entity* entity, utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(dat::base::Entity* entity, utl::media::Image* image);
  void overlay_pixel(utl::media::Image* image, ImVec2 image_size);

private:
  dat::Graph* dat_graph;
  dat::Set* dat_set;

  vector<gui_element::Stream*> vec_gui_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  string name;
  bool* show_window;
  int current_tab_id = 0;
};

}
