#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class GUI_image;
class GUI_video;
class TAB_render;
class RND_panel;
class UTL_device;
class UTL_capture;


class GUI_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_capture(GUI* gui, bool* show_window, string name);
  ~GUI_capture();

  //Main function
  void design_panel();

  //Subfunction
  void capture_devices();
  void capture_command();
  void truc();

private:
  GUI_video* gui_video;
  GUI_image* gui_image;
  GUI* gui;
  RND_panel* gui_render_panel;
  UTL_device* utl_device;
  UTL_capture* utl_capture;

  string stream_node;
  int item_width;
};

#endif
