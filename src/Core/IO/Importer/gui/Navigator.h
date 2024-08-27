#pragma once

#include <Utility/GUI/Navigator/Navigator.h>

namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
namespace io::imp::gui{class Panel;}
namespace utl::gui{class Navigator;}


namespace io::imp::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(io::imp::gui::Panel* gui_panel);
  ~Navigator();

public:
  //Main function
  void init_navigator();
  void draw_tab(int width);
  void item_operation(utl::base::Path path);
  
private:
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  utl::gui::Navigator* utl_navigator;
};

}
