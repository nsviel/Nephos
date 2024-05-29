#pragma once

#include <Utility/Specific/Common.h>


namespace utl::gui::tree{

struct Node{
  //---------------------------

  string name;
  string type;
  string path;
  float size = -1;
  bool already_open = false;
  bool end_folder;
  int leaf_idx;
  int leaf_nb;

  //---------------------------
};

}
