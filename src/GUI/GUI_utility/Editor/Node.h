#pragma once

#include <Utility/UTL_specific/common.h>
#include <imgui/node/imgui_node_editor.h>

class Node;


namespace gui::editor{

class Node
{
public:
  //Constructor / Destructor
  Node(Node* gui);
  ~Node();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void node_editor();

private:
};

}
