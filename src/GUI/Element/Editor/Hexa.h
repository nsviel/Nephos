#pragma once

#include <Utility/Specific/Common.h>
#include <imgui/editor/editor_memory.h>


namespace gui::element::editor{

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
