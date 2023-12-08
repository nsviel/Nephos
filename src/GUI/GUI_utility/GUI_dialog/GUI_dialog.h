#pragma once

#include <GUI_utility/Base_nsp.h>
#include <UTL_specific/common.h>

class GUI;


class GUI_dialog : public gui::base::Panel
{
public:
  //Constructor / Destructor
  GUI_dialog(GUI* gui, bool* show_window, string name);
  ~GUI_dialog();

  //Main function
  void design_panel();

  //Subfunction
  void capture_command();

private:
  int item_width;
};
