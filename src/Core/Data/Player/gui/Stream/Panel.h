#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace dat::ply{class Node;}
namespace dat::stream::gui{class Overlay;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace rnd::gui{class Stream;}
namespace utl::base{class Element;}
namespace utl::media{class Image;}


namespace dat::stream::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::ply::Node* node_player, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel(dat::base::Entity* entity);

  //All devices
  void draw_stream_tabbar(dat::base::Entity* entity);
  void draw_stream_image(utl::media::Image* image, ImVec2 image_size, int idx);

private:
  dat::gph::Selection* dat_selection;
  dat::elm::Set* dat_set;
  dat::stream::gui::Overlay* gui_overlay;

  std::vector<rnd::gui::Stream*> vec_stream;
  std::string open_tab = "";
  std::string name;
  bool* show_window;
};

}
