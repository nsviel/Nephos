#pragma once

#include <GUI/GUI_utility/Widget/Tree_node.h>
#include <Utility/Specific/common.h>


struct Tree_filler{
  //---------------------------

  //Pathes
  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  Tree_node* node_selected;

  //---------------------------
};
