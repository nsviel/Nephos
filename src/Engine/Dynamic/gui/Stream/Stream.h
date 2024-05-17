#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Graph;}
namespace eng{class Node;}
namespace dat{class Set;}
namespace rnd{class Stream;}
namespace utl::base{class Element;}
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
  void init();
  void run_panel();
  void design_panel(utl::base::Element* element);

  //All devices
  void draw_set_tabbar(dat::base::Set* set);
  void draw_stream_tabbar(dat::base::Entity* entity);
  void draw_stream_image(utl::media::Image* image, ImVec2 image_size);

  //Overlay
  void compute_hovered_pixel(utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered);
  void overlay_capture(dat::base::Entity* entity, utl::media::Image* image, ImVec2 image_size, ImVec2 image_pose);
  void overlay_information(dat::base::Entity* entity, utl::media::Image* image);
  void overlay_pixel(utl::media::Image* image, ImVec2 image_size);

private:
  eng::Node* node_engine;
  dat::Graph* dat_graph;
  dat::Set* dat_set;

  vector<rnd::Stream*> vec_stream;
  ImVec2 hovered_pixel;
  string open_tab = "";
  string name;
  bool* show_window;
  int current_tab_id = 0;
};

}
