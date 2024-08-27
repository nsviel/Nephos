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

  inline bool& get_open_tab(){return open_tab;}
  inline utl::gui::Navigator* get_utl_navigator(){return utl_navigator;}

private:
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  utl::gui::Navigator* utl_navigator;

  bool open_tab;
};

}
