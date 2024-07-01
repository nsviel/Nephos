#pragma once

#include <Loader/gui/Navigator/Structure/File.h>
#include <imgui/core/imgui.h>
#include <vector>
#include <string>


namespace ldr::gui::navigator{

struct Structure{
  //---------------------------

  std::vector<ldr::gui::navigator::File> vec_folder;
  std::vector<ldr::gui::navigator::File> vec_file;
  std::string default_path = "";
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;

  //---------------------------
};

}
