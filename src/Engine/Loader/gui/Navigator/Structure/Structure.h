#pragma once

#include <Loader/gui/Navigator/Structure/File.h>
#include <imgui/core/imgui.h>
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
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;

  //---------------------------
};

}
