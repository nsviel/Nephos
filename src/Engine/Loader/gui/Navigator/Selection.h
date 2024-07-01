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

  void control_selection(ldr::gui::navigator::File& file, bool& already_selected);
  void item_selection_truc(utl::base::Path& path);

  void selection_item(ldr::gui::navigator::File& file);
  void selection_folder(ldr::gui::navigator::File& file);
  void selection_file(ldr::gui::navigator::File& file);

protected:
  ldr::gui::navigator::Structure* nav_struct;
};

}
