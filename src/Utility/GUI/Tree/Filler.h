#pragma once

#include <Utility/GUI/Tree/Node.h>
#include <Utility/Specific/Common.h>


namespace utl::gui::tree{

struct Filler{
  //---------------------------

  //Pathes
  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  utl::gui::tree::Node* node_selected;

  //Function
  std::function<void(string path)> fct_on_click;

  //---------------------------
};

}
