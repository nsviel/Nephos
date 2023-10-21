#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include <Tab/Base/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class Struct_render_panel;


class GUI_dialog : public BASE_panel
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
  Struct_render_panel* struct_render_panel;

  int item_width;
};

#endif
