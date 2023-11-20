#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class GUI_image;
class GUI_stream;
class TAB_render;
class RND_panel;
class V4L2_camera;
class V4L2_device;
class UTL_capture;


class GUI_camera : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_camera(GUI* gui, bool* show_window, string name);
  ~GUI_camera();

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
  V4L2_device* v4l2_device;
  V4L2_camera* v4l2_stream;
  UTL_capture* utl_capture;

  string stream_node;
  int item_width;
};

#endif
