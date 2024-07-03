#pragma once

#include <imgui/core/imgui.h>
#include <iostream>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class File;}
namespace utl::base{class Path;}


namespace ldr::gui::navigator{

class Selection
{
public:
  //Constructor / Destructor
  Selection(ldr::gui::navigator::Structure* nav_struct);
  ~Selection();

public:
  //Main function
  void selection_item(utl::base::Path& path, ldr::gui::navigator::File& file);

  //Subfunction
  void control_selection(ldr::gui::navigator::File& file, bool& already_selected);
  void double_click(utl::base::Path& path, ldr::gui::navigator::File& file);
  void clear_selection();
  void item_operation();

protected:
  ldr::gui::navigator::Structure* nav_struct;

  ImVector<int> vec_selection;
};

}
