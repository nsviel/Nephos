#ifndef GUI_KINECT_CAPTURE_H
#define GUI_KINECT_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;
class GUI_stream;


class GUI_kinect_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_kinect_capture(GUI* gui, bool* show_window, string name);
  ~GUI_kinect_capture();

  //Main function
  void draw_camera_color(Struct_k4a_device* device);

private:
  GUI* gui;
  GUI_stream* gui_stream;
};

#endif
