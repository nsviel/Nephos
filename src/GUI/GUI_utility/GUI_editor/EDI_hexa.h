#pragma once

#include <UTL_specific/common.h>
#include <imgui/editor/editor_memory.h>

class GUI;


namespace gui::editor{

class EDI_hexa
{
public:
  //Constructor / Destructor
  EDI_hexa(GUI* gui);
  ~EDI_hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

}
