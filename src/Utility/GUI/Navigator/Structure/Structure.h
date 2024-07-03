#pragma once

#include <Utility/GUI/Navigator/Structure/Item.h>
#include <Utility/Base/Type/Path.h>
#include <functional>
#include <vector>
#include <string>


namespace utl::gui::navigator{

struct Structure{
  //---------------------------

  //Function
  std::vector<std::function<void()>> vec_icon;
  std::function<void(utl::base::Path)> fct_item_operation;

  //Data
  std::vector<utl::gui::navigator::Item> vec_item;
  std::string default_path = "";
  bool with_bookmark = true;

  //---------------------------
};

}
