#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Selection;}
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
  void run_panel();
  void design_panel(dat::base::Entity* entity);

  //All devices
  void draw_stream_tabbar(dat::base::Entity* entity);
  void draw_stream_image(utl::media::Image* image, ImVec2 image_size);

private:
  eng::Node* node_engine;
  dat::Selection* dat_selection;
  dat::Set* dat_set;
  dyn::gui::Overlay* gui_overlay;

  vector<rnd::Stream*> vec_stream;
  string open_tab = "";
  string name;
  bool* show_window;
};

}
