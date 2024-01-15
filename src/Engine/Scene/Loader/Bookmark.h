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
  void add_item(string path, bool supressible);

  inline vector<Item> get_vec_bookmark(){return vec_bookmark;}
private:
  vector<Item> vec_bookmark;
  string path_file;
};

}
