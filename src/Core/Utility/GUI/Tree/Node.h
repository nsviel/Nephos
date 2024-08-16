#pragma once

#include <string>


namespace utl::gui::tree{

struct Node{
  //---------------------------

  std::string name;
  std::string type;
  std::string path;
  float size = -1;
  bool already_open = false;
  bool end_folder;
  int leaf_idx;
  int leaf_nb;

  //---------------------------
};

}
