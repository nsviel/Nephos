#pragma once

namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class Organisation;}
namespace ldr::gui::navigator{class Selection;}
namespace ldr::gui::navigator{class File;}
namespace utl::base{class Path;}


namespace ldr::gui::navigator{

class Content
{
public:
  //Constructor / Destructor
  Content(ldr::gui::navigator::Structure* nav_struct);
  ~Content();

public:
  //Main function
  void draw_content(utl::base::Path& path);

  //Subfunction
  void draw_item(ldr::gui::navigator::File& file);
  void draw_icon(ldr::gui::navigator::File& file);

protected:
  ldr::gui::navigator::Structure* nav_struct;
  ldr::gui::navigator::Organisation* nav_organisation;
  ldr::gui::navigator::Selection* nav_selection;
};

}
