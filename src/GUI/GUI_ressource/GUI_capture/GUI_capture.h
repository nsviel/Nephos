#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class GUI_image;
class GUI_video;
class TAB_render;
class RND_panel;


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
  RND_panel* gui_render_panel;

  int item_width;
};

#endif
