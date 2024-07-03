#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class Organisation;}
namespace ldr::gui::navigator{class Header;}
namespace ldr::gui::navigator{class Selection;}
namespace ldr::gui::navigator{class File;}
namespace utl::base{class Path;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator();
  ~Navigator();

public:
  //Main function
  void draw_navigator(utl::base::Path& path);

  //Subfunction
  void draw_content(utl::base::Path& path);
  void draw_item(ldr::gui::navigator::File& file);

protected:
  ldr::gui::navigator::Structure* nav_struct;
  ldr::gui::navigator::Organisation* nav_organisation;
  ldr::gui::navigator::Header* nav_header;
  ldr::gui::navigator::Selection* nav_selection;
};

}
