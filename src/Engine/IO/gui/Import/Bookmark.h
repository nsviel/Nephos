#pragma once

#include <string>

namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::bookmark{class Manager;}
namespace ldr::gui::importer{class Panel;}
namespace ldr::gui::importer{class Navigator;}


namespace ldr::gui::importer{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(ldr::gui::importer::Panel* gui_panel);
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
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  ldr::gui::importer::Navigator* gui_navigator;
};

}
