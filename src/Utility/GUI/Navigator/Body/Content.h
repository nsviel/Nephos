#pragma once

namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class Organisation;}
namespace utl::gui::navigator{class Selection;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Path;}


namespace utl::gui::navigator{

class Content
{
public:
  //Constructor / Destructor
  Content(utl::gui::navigator::Structure* nav_struct);
  ~Content();

public:
  //Main function
  void draw_content(utl::base::Path& path);

  //Subfunction
  void draw_item(utl::gui::navigator::Item& file);
  void draw_icon(utl::gui::navigator::Item& file);

protected:
  utl::gui::navigator::Structure* nav_struct;
  utl::gui::navigator::Organisation* nav_organisation;
  utl::gui::navigator::Selection* nav_selection;
};

}
