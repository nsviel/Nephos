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
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  io::imp::Bookmark* io_bookmark;
  io::imp::gui::Navigator* gui_navigator;
};

}
