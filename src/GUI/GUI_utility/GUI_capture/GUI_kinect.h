#ifndef GUI_KINECT_H
#define GUI_KINECT_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class GUI_image;
class GUI_stream;
class TAB_render;
class RND_panel;
class V4L2_device;
class UTL_capture;


class GUI_kinect : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_kinect(GUI* gui, bool* show_window, string name);
  ~GUI_kinect();

  //Main function
  void design_panel();

  //Subfunction
  void capture_devices();
  void capture_command();

private:
  GUI_stream* gui_stream;
  GUI_image* gui_image;
  GUI* gui;
  RND_panel* gui_render_panel;
  V4L2_device* utl_device;
  UTL_capture* utl_capture;

  string stream_node;
  int item_width;
};

#endif
