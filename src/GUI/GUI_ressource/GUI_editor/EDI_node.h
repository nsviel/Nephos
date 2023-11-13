#ifndef GUI_EDITOR_NODE_H
#define GUI_EDITOR_NODE_H

#include <ELE_specific/common.h>
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

#endif
