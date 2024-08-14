#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io{class Structure;}
namespace io{class Importer;}
namespace io::gui::importer{class Panel;}
namespace io::gui::importer{class Navigator;}
namespace utl::base{class Path;}


namespace io::gui::importer{

class Operation
{
public:
  //Constructor / Destructor
  Operation(io::gui::importer::Panel* gui_panel);
  ~Operation();

public:
  //Main function
  void init_navigator();
  void draw_header();

  //Subfunction
  void item_operation(utl::base::Path path);

private:
  io::Structure* io_struct;
  io::Importer* io_importer;
  io::gui::importer::Navigator* gui_navigator;
};

}
