#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
namespace io::imp::gui{class Panel;}
namespace io::imp::gui{class Navigator;}
namespace utl::base{class Path;}


namespace io::imp::gui{

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
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  io::imp::gui::Navigator* gui_navigator;
};

}
