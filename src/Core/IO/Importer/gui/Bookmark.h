#pragma once

#include <string>

namespace io::imp{class Structure;}
namespace io::imp{class Loader;}
namespace io::imp{class Bookmark;}
namespace io::imp::gui{class Panel;}
namespace utl::gui{class Navigator;}


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
  io::imp::Loader* io_loader;
  io::imp::Bookmark* io_bookmark;
  utl::gui::Navigator* utl_navigator;
};

}
