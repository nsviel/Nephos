#pragma once

#include <GUI_utility/Widget/Tree_node.h>
#include <UTL_specific/common.h>


struct Struct_init{
  //---------------------------

  bool remove_old = true;
  float scale = 1;

  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  Tree_node* node_selected;

  //---------------------------
};
