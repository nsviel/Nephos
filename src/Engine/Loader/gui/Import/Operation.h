#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui::importer{class Panel;}


namespace ldr::gui::importer{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ldr::gui::importer::Panel* gui_panel);
  ~Operation();

public:
  //Main function
  void draw_header();

  //Subfunction
  void item_operation();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
};

}
