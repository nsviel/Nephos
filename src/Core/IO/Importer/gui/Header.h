#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io::imp{class Structure;}
namespace io::imp::gui{class Panel;}
namespace io::imp::gui{class Navigator;}
namespace utl::base{class Path;}


namespace io::imp::gui{

class Header
{
public:
  //Constructor / Destructor
  Header(io::imp::gui::Panel* gui_panel);
  ~Header();

public:
  //Main function
  void draw_header();

  //Subfunction

private:
  io::imp::Structure* io_struct;
  io::imp::gui::Navigator* gui_navigator;
};

}
