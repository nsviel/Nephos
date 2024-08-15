#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace dyn{class Node;}
namespace dyn::gui::stream{class Overlay;}
namespace dat::graph{class Selection;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace core{class Node;}
namespace rnd::gui{class Stream;}
namespace utl::base{class Element;}
namespace utl::media{class Image;}


namespace dyn::gui::stream{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dyn::Node* node_dynamic, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel(dat::base::Entity* entity);

  //All devices
  void draw_stream_tabbar(dat::base::Entity* entity);
  void draw_stream_image(utl::media::Image* image, ImVec2 image_size, int idx);

private:
  core::Node* node_core;
  dat::graph::Selection* dat_selection;
  dat::elm::Set* dat_set;
  dyn::gui::stream::Overlay* gui_overlay;

  std::vector<rnd::gui::Stream*> vec_stream;
  std::string open_tab = "";
  std::string name;
  bool* show_window;
};

}
