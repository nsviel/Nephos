#pragma once

#include <Utility/GUI/Navigator/Navigator.h>

namespace ldr{class Structure;}
namespace ldr::gui::importer{class Panel;}
namespace utl::gui{class Navigator;}


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

  inline bool& get_open_tab(){return open_tab;}
  inline utl::gui::Navigator* get_utl_navigator(){return utl_navigator;}

private:
  ldr::Structure* ldr_struct;
  utl::gui::Navigator* utl_navigator;

  bool open_tab;
};

}