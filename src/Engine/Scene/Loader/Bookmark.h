#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Scene/Loader/Item.h>

namespace eng::scene{


class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(eng::scene::Node* node_scene);
  ~Bookmark();

public:
  void init();
  void add_abs_path(string path);
  void add_relative_path(string path);
  bool is_path_bookmarked(string path);

  inline vector<Item> get_vec_bookmark(){return vec_bookmark;}

private:
  vector<Item> vec_bookmark;
  string path_file;
};

}
