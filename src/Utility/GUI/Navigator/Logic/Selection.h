#pragma once

#include <imgui/core/imgui.h>
#include <iostream>
#include <string>
#include <vector>

namespace utl::gui{class Navigator;}
namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Path;}


namespace utl::gui::navigator{

class Selection
{
public:
  //Constructor / Destructor
  Selection(utl::gui::Navigator* navigator);
  ~Selection();

public:
  //Main function
  void selection_item(utl::base::Path& path, utl::gui::navigator::Item& file);

  //Subfunction
  void control_selection(utl::base::Path& path, utl::gui::navigator::Item& file, bool& already_selected);
  void double_click(utl::base::Path& path, utl::gui::navigator::Item& file);
  void clear_selection();
  void item_operation();
  void update_selected_path();

private:
  utl::gui::navigator::Structure* nav_struct;
};

}
