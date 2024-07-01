#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::gui::navigator{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui::navigator{class File;}
namespace ldr::bookmark{class Manager;}
namespace utl::base{class Path;}


namespace ldr::gui::navigator{

class Selection
{
public:
  //Constructor / Destructor
  Selection(ldr::gui::navigator::Structure* nav_struct);
  ~Selection();

public:
  //Main function
  void item_selection(utl::base::Path& path);
  void make_selection(ldr::gui::navigator::File& file, bool& already_selected);

protected:
  ldr::gui::navigator::Structure* nav_struct;
};

}
