#pragma once

#include <Utility/Specific/Common.h>
#include <imgui/node/imgui_node_editor.h>


namespace utl::gui::editor{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main function
  void design_panel();

  //Subfunction
  void node_editor();

private:
};

}
