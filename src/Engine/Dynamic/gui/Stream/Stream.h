#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace dyn{class Node;}
namespace dyn::gui{class Overlay;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace eng{class Node;}
namespace itf::gui{class Stream;}
namespace utl::base{class Element;}
namespace utl::media{class Image;}


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
  void draw_stream_image(utl::media::Image* image, ImVec2 image_size, int idx);

private:
  eng::Node* node_engine;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  dyn::gui::Overlay* gui_overlay;

  std::vector<itf::gui::Stream*> vec_stream;
  std::string open_tab = "";
  std::string name;
  bool* show_window;
};

}
