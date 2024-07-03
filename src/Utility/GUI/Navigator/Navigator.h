#pragma once

#include <functional>

namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class Header;}
namespace utl::gui::navigator{class Content;}
namespace utl::gui::navigator{class Selection;}
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
  void make_selection_operation();

  //Subfunction
  void add_fct_item_operation(std::function<void(utl::base::Path)> func);
  void add_fct_item_icon(std::function<void()> func);

  inline utl::gui::navigator::Structure* get_nav_struct(){return nav_struct;}
  inline utl::gui::navigator::Selection* get_nav_selection(){return nav_selection;}

private:
  utl::gui::navigator::Structure* nav_struct;
  utl::gui::navigator::Selection* nav_selection;
  utl::gui::navigator::Header* nav_header;
  utl::gui::navigator::Content* nav_content;
};

}
