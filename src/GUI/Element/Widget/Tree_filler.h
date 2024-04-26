#pragma once

#include <GUI/Element/Widget/Tree_node.h>
#include <Utility/Specific/Common.h>


struct Tree_filler{
  //---------------------------

  //Pathes
  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  Tree_node* node_selected;

  //Function
  std::function<void(string path)> fct_on_click;

  //---------------------------
};
