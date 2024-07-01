#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class Organisation;}
namespace ldr::gui::navigator{class Header;}
namespace ldr::gui::navigator{class Selection;}
namespace ldr::io{class Importer;}
namespace ldr::gui::navigator{class File;}
namespace ldr::bookmark{class Manager;}
namespace utl::base{class Path;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(ldr::Node* node_loader, bool with_bookmark);
  ~Navigator();

public:
  //Main function
  void draw_navigator(utl::base::Path& path);

  //Subfunction
  void draw_content(utl::base::Path& path);
  void draw_item_content(utl::base::Path& path);
  void draw_content_file(ldr::gui::navigator::File& file);
  void draw_bookmark_icon(ldr::gui::navigator::File& bookmark);

  virtual void item_operation(){}

protected:
  ldr::gui::navigator::Structure* nav_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  ldr::gui::navigator::Organisation* nav_organisation;
  ldr::gui::navigator::Header* nav_header;
  ldr::gui::navigator::Selection* nav_selection;
};

}
