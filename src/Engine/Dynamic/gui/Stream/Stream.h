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
namespace dyn::gui{class Overlay;}


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

private:
  eng::Node* node_engine;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
  dyn::gui::Overlay* gui_overlay;

  vector<rnd::Stream*> vec_stream;
  string open_tab = "";
  string name;
  bool* show_window;
};

}
