#pragma once

#include <Loader/gui/Navigator/Structure/File.h>
#include <functional>
#include <vector>
#include <string>


namespace ldr::gui::navigator{

struct Structure{
  //---------------------------

  std::vector<ldr::gui::navigator::File> vec_item;
  std::vector<std::function<void()>> vec_icon;
  std::function<void()> fct_item_operation;
  std::string default_path = "";
  bool with_bookmark = true;

  //---------------------------
};

}
