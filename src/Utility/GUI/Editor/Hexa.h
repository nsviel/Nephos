#pragma once

#include <Utility/Specific/common.h>
#include <imgui/editor/editor_memory.h>


namespace gui::editor{

class Hexa
{
public:
  //Constructor / Destructor
  Hexa();
  ~Hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

}
