#pragma once

#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Data/src/Loader/Item.h>

namespace eng::scene{


class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(eng::scene::Node* node_scene);
  ~Bookmark();

public:
  //Main function
  void init();

  //Item management
  void add_abs_path(string path);
  void add_relative_path(string path);
  void remove_path(string path);

  //Subfunction
  bool is_path_bookmarked(string path);
  void save_on_file();

  inline list<Item> get_list_bookmark(){return list_bookmark;}

private:
  list<Item> list_bookmark;
  string path_bookmark_file;
};

}
