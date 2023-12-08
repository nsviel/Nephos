#pragma once

#include <UTL_specific/common.h>
#include <imgui/editor/editor_memory.h>

class GUI;


namespace gui::editor{

class Hexa
{
public:
  //Constructor / Destructor
  Hexa(GUI* gui);
  ~Hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

}
