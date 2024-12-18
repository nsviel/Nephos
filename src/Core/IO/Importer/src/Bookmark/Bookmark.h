#pragma once

#include <string>
#include <list>

namespace io::imp{class Node;}
namespace io::imp::bookmark{class Item;}


namespace io::imp{

class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(io::imp::Node* node_importer);
  ~Bookmark();

public:
  //Main function
  void init();

  //Item management
  void load_file_bookmark();
  void save_file_bookmark();
  void remove_path(std::string path);

  //Subfunction
  void add_abs_path(std::string path);
  void add_relative_path(std::string path);
  bool is_path_bookmarked(std::string path);
  void sort_list_item();

  inline std::list<io::imp::bookmark::Item> get_list_item(){return list_item;}

private:
  std::list<io::imp::bookmark::Item> list_item;
  std::string path_bookmark_file;
};

}
