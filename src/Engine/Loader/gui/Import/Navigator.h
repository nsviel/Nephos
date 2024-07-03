#pragma once

#include <Loader/gui/Navigator/Navigator.h>

namespace ldr{class Structure;}
namespace ldr::gui::importer{class Panel;}
namespace ldr::gui{class Navigator;}


namespace ldr::gui::importer{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(ldr::gui::importer::Panel* gui_panel);
  ~Navigator();

public:
  //Main function
  void draw_tab(int width);

private:
  ldr::Structure* ldr_struct;
  ldr::gui::Navigator* gui_navigator;
};

}
