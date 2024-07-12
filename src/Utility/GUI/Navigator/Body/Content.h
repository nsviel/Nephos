#pragma once

#include <string>

namespace utl::gui{class Navigator;}
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
  Content(utl::gui::Navigator* navigator);
  ~Content();

public:
  //Main function
  void draw_content(utl::base::Path& path);

  //Subfunction
  void draw_table(utl::base::Path& path);
  void draw_item(utl::gui::navigator::Item& file);
  void draw_icon(utl::gui::navigator::Item& file);

private:
  utl::gui::navigator::Structure* nav_struct;
  utl::gui::navigator::Organisation* nav_organisation;
  utl::gui::navigator::Selection* nav_selection;

  std::string curr_dir = "";
};

}
