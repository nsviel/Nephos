#pragma once

#include <Utility/GUI/Tree/Node.h>
#include <functional>
#include <vector>
#include <string>


namespace utl::gui::tree{

struct Filler{
  //---------------------------

  //Pathes
  std::vector<std::string> accepted_format;
  std::vector<std::string> vec_path_folder;
  std::vector<std::string> vec_path_file;

  //Selection
  bool is_selection = false;
  utl::gui::tree::Node* node_selected;

  //Function
  std::function<void(std::string path)> fct_on_click;

  //---------------------------
};

}
