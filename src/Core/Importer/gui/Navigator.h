#pragma once

#include <Utility/GUI/Navigator/Navigator.h>

namespace io{class Structure;}
namespace io::imp::gui{class Panel;}
namespace utl::gui{class Navigator;}


namespace io::imp::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(io::gui::importer::Panel* gui_panel);
  ~Navigator();

public:
  //Main function
  void draw_tab(int width);

  inline bool& get_open_tab(){return open_tab;}
  inline utl::gui::Navigator* get_utl_navigator(){return utl_navigator;}

private:
  io::Structure* io_struct;
  utl::gui::Navigator* utl_navigator;

  bool open_tab;
};

}
