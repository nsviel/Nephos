#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

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
  void item_bookmark(std::string path);
  void item_bookmark_icon();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  ldr::gui::importer::Navigator* gui_navigator;
};

}
