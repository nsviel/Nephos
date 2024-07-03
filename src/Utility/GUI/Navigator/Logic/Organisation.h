#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace utl::gui{class Navigator;}
namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Path;}


namespace utl::gui::navigator{

class Organisation
{
public:
  //Constructor / Destructor
  Organisation(utl::gui::Navigator* navigator);
  ~Organisation();

public:
  //Main function
  void update_item_list(utl::base::Path& path);

  //Subfunction
  void recolt_items(std::string& directory);
  void sort_items();
  void insert_file(std::vector<utl::gui::navigator::Item>& vec_item, std::string& path, int& ID);
  void insert_folder(std::vector<utl::gui::navigator::Item>& vec_item, std::string& path, int& ID);
  bool is_hidden_file(std::string& path);

private:
  utl::gui::navigator::Structure* nav_struct;

  std::vector<utl::gui::navigator::Item> vec_folder;
  std::vector<utl::gui::navigator::Item> vec_file;
  std::string curr_dir = "";
};

}
