#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io::imp{class Structure;}
namespace io::imp::gui{class Panel;}
namespace utl::gui{class Navigator;}
namespace utl::gui::navigator{class Structure;}
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
  void draw_loader();
  void draw_path();
  void draw_operation();

private:
  io::imp::Structure* io_struct;
  utl::gui::Navigator* utl_navigator;
  utl::gui::navigator::Structure* nav_struct;
};

}
