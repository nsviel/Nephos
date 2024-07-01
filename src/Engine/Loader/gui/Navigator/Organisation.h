#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui::navigator{class File;}
namespace ldr::bookmark{class Manager;}
namespace utl::base{class Path;}
namespace ldr::gui::navigator{class Structure;}


namespace ldr::gui::navigator{

class Organisation
{
public:
  //Constructor / Destructor
  Organisation(ldr::gui::navigator::Structure* nav_struct);
  ~Organisation();

public:
  //Main function
  void item_organisation(std::vector<std::string>& vec_path);

  //Subfunction
  void insert_file(std::string& path, int& ID);
  void insert_folder(std::string& path, int& ID);
  void sort_data();
  bool is_hidden_file(std::string& path);

protected:
  ldr::gui::navigator::Structure* nav_struct;
};

}
