#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <Element/Base/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_image;
class GUI_video;
class GUI_render;
class GUI_render_panel;


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
  GUI_video* gui_video;
  GUI_image* gui_image;
  GUI* gui;
  GUI_render_panel* gui_render_panel;

  int item_width;
};

#endif
