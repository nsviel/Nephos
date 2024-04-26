#pragma once

#include <Utility/Specific/Common.h>
#include <imgui/node/imgui_node_editor.h>


namespace gui::element::editor{

class Node : public utl::type::Node
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
