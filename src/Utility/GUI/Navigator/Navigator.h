#pragma once

#include <functional>

namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class Header;}
namespace utl::gui::navigator{class Content;}
namespace utl::base{class Path;}


namespace utl::gui{

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
  void add_fct_item_operation(std::function<void()> func);
  void add_fct_item_icon(std::function<void()> func);

private:
  utl::gui::navigator::Structure* nav_struct;
  utl::gui::navigator::Header* nav_header;
  utl::gui::navigator::Content* nav_content;
};

}
