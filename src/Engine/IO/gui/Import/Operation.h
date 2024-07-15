#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui::importer{class Panel;}
namespace ldr::gui::importer{class Navigator;}
namespace utl::base{class Path;}


namespace ldr::gui::importer{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ldr::gui::importer::Panel* gui_panel);
  ~Operation();

public:
  //Main function
  void init_navigator();
  void draw_header();

  //Subfunction
  void item_operation(utl::base::Path path);

private:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::gui::importer::Navigator* gui_navigator;
};

}
