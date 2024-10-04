#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <memory>
#include <vector>

namespace dat::img{class Node;}
namespace dat::img::gui{class Overlay;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace dat::img::gui{class Stream;}
namespace utl::base{class Element;}
namespace utl::base{class Image;}
namespace utl::base{class Data;}


namespace dat::img::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::img::Node* node_image, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel(std::shared_ptr<dat::base::Entity> entity);

  //All devices
  void draw_stream_tabbar(std::shared_ptr<dat::base::Entity> entity);
  void draw_stream_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image, ImVec2 image_size, int idx);

private:
  dat::gph::Selection* gph_selection;
  dat::elm::Set* dat_set;
  dat::img::gui::Overlay* gui_overlay;

  std::vector<dat::img::gui::Stream*> vec_stream;
  std::string open_tab = "";
  std::string name;
  bool* show_window;
};

}
