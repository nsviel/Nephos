#pragma once

#include <UTL_specific/common.h>
#include <GUI_utility/Base_nsp.h>

class GUI;
class EDI_text;


namespace gui::dev::panel{

class Editor : public gui::base::Panel
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
