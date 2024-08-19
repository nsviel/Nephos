#pragma once

#include <Utility/GUI/Navigator/Structure/Item.h>
#include <Utility/Base/Data/Path.h>
#include <imgui/core/imgui.h>
#include <functional>
#include <vector>
#include <string>


namespace utl::gui::navigator{

struct Structure{
  //---------------------------

  //Function
  std::vector<std::function<void(std::string path)>> vec_icon;
  std::function<void(utl::base::Path)> fct_item_operation;
  std::function<void(utl::base::Path)> fct_item_selection;

  //Data
  std::vector<utl::gui::navigator::Item> vec_item;
  std::vector<std::string> vec_selected_path;
  std::string default_path = "";
  ImVector<int> vec_selected_idx;
  bool with_bookmark = true;

  //---------------------------
};

}
