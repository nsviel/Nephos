#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_image;
class Panel;


class GUI_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_capture(GUI* gui, bool* show_window, string name);
  ~GUI_capture();

  //Main function
  void design_panel();

  //Subfunction
  void capture_command();

private:
  GUI_image* gui_image;
  Panel* panel;

  int item_width;
};

#endif
