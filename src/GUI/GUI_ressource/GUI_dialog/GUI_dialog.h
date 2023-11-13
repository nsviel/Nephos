#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class RND_panel;


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
  RND_panel* gui_render_panel;

  int item_width;
};

#endif
