#pragma once

#include <UTL_specific/common.h>
#include <imgui/node/imgui_node_editor.h>

class EDI_node;


class EDI_node
{
public:
  //Constructor / Destructor
  EDI_node(EDI_node* gui);
  ~EDI_node();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void node_editor();

private:
};
