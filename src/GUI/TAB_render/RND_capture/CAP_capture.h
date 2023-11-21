#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;
class GUI_stream;
class CAP_kinect;


class CAP_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  CAP_capture(GUI* gui, bool* show_window, string name);
  ~CAP_capture();

  //Main function
  void design_panel();
  void draw_camera_color();

private:
  GUI* gui;
  GUI_stream* gui_stream;
  CAP_kinect* gui_kinect;
};

#endif
