#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace utl::gui::navigator{class Structure;}
namespace utl::gui::navigator{class File;}
namespace utl::base{class Path;}


namespace utl::gui::navigator{

class Organisation
{
public:
  //Constructor / Destructor
  Organisation(utl::gui::navigator::Structure* nav_struct);
  ~Organisation();

public:
  //Main function
  void update_item_list(utl::base::Path& path);

  //Subfunction
  void recolt_items(std::string& directory);
  void sort_items();
  void insert_file(std::vector<utl::gui::navigator::File>& vec_item, std::string& path, int& ID);
  void insert_folder(std::vector<utl::gui::navigator::File>& vec_item, std::string& path, int& ID);
  bool is_hidden_file(std::string& path);

protected:
  utl::gui::navigator::Structure* nav_struct;

  std::vector<utl::gui::navigator::File> vec_folder;
  std::vector<utl::gui::navigator::File> vec_file;
  std::string curr_dir = "";
};

}
