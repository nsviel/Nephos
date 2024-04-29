#pragma once

#include <Utility/Specific/Common.h>

namespace eng::loader{class Item;}
namespace sce{class Node;}


namespace sce{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(sce::Node* node_scene);
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
  void sort_list_bookmark();
  void save_on_file();

  inline list<eng::loader::Item> get_list_bookmark(){return list_bookmark;}

private:
  list<eng::loader::Item> list_bookmark;
  string path_bookmark_file;
};

}
