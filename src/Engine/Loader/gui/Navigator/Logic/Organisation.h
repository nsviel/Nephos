#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class File;}
namespace utl::base{class Path;}


namespace ldr::gui::navigator{

class Organisation
{
public:
  //Constructor / Destructor
  Organisation(ldr::gui::navigator::Structure* nav_struct);
  ~Organisation();

public:
  //Main function
  void update_item_list(utl::base::Path& path);

  //Subfunction
  void recolt_items(std::string& directory);
  void sort_items();
  void insert_file(std::vector<ldr::gui::navigator::File>& vec_item, std::string& path, int& ID);
  void insert_folder(std::vector<ldr::gui::navigator::File>& vec_item, std::string& path, int& ID);
  bool is_hidden_file(std::string& path);

protected:
  ldr::gui::navigator::Structure* nav_struct;

  std::vector<ldr::gui::navigator::File> vec_folder;
  std::vector<ldr::gui::navigator::File> vec_file;
  std::string curr_dir = "";
};

}
