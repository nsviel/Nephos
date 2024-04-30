#pragma once

#include <string>
#include <list>

namespace ldr{class Node;}
namespace ldr{class Item;}


namespace ldr{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(ldr::Node* node_loader);
  ~Bookmark();

public:
  //Main function
  void init();

  //Item management
  void add_abs_path(std::string path);
  void add_relative_path(std::string path);
  void remove_path(std::string path);

  //Subfunction
  bool is_path_bookmarked(std::string path);
  void sort_list_item();
  void save_on_file();

  inline std::list<ldr::Item> get_list_item(){return list_item;}

private:
  std::list<ldr::Item> list_item;
  std::string path_bookmark_file;
};

}
