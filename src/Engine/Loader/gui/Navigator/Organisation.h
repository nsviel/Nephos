#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr::gui::navigator{class Structure;}
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
  void recolt_items(utl::base::Path& path);
  void sort_items();

  //Subfunction
  void insert_file(std::string& path, int& ID);
  void insert_folder(std::string& path, int& ID);
  bool is_hidden_file(std::string& path);

protected:
  ldr::gui::navigator::Structure* nav_struct;
};

}
