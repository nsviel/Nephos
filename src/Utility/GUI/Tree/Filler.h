#pragma once

#include <Utility/GUI/Tree/Node.h>
#include <Utility/Specific/Common.h>


namespace utl::gui::tree{

struct Filler{
  //---------------------------

  //Pathes
  std::vector<string> accepted_format;
  std::vector<string> vec_path_folder;
  std::vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  utl::gui::tree::Node* node_selected;

  //Function
  std::function<void(std::string path)> fct_on_click;

  //---------------------------
};

}
