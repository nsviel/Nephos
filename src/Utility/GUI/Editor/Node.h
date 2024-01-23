#pragma once

#include <Utility/Specific/common.h>
#include <imgui/node/imgui_node_editor.h>


namespace gui::editor{

class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void node_editor();

private:
};

}
