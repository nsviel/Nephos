#pragma once

#include <string>

namespace io{class Structure;}
namespace io{class Importer;}
namespace io::imp::bookmark{class Manager;}
namespace io::imp::gui{class Panel;}
namespace io::imp::gui{class Navigator;}


namespace io::imp::gui{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(io::gui::importer::Panel* gui_panel);
  ~Bookmark();

public:
  //Main function
  void init_navigator();
  void draw_tab(int width);

  //Subfunction
  void draw_content();
  void bookmark_button(std::string path);
  void bookmark_icon(std::string path);

private:
  io::Structure* io_struct;
  io::Importer* io_importer;
  io::bookmark::Manager* io_bookmark;
  io::gui::importer::Navigator* gui_navigator;
};

}
