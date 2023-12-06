#pragma once

#include <UTL_specific/common.h>
#include <GUI_base/BASE_panel.h>

class GUI;
class EDI_text;


namespace dev{

class Editor : public BASE_panel
{
public:
  //Constructor / Destructor
  Editor(GUI* gui, bool* show_window, string name);
  ~Editor();

public:
  //Main function
  void design_panel();

private:
  EDI_text* editor;
};

}
