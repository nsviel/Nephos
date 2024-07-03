#pragma once

#include <Utility/GUI/Navigator/Structure/File.h>
#include <functional>
#include <vector>
#include <string>


namespace utl::gui::navigator{

struct Structure{
  //---------------------------

  std::vector<utl::gui::navigator::File> vec_item;
  std::vector<std::function<void()>> vec_icon;
  std::function<void()> fct_item_operation;
  std::string default_path = "";
  bool with_bookmark = true;

  //---------------------------
};

}
