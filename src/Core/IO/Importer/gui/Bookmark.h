#pragma once

#include <string>

namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
namespace io::imp{class Bookmark;}
namespace io::imp::gui{class Panel;}
namespace io::imp::gui{class Navigator;}


namespace io::imp::gui{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(io::imp::gui::Panel* gui_panel);
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