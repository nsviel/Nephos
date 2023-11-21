#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;
class GUI_stream;
class Kinect;
class Struct_kinect;


class CAP_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  CAP_capture(GUI* gui, bool* show_window, string name);
  ~CAP_capture();

  //Main function
  void design_panel();

  //Subfunction
  void draw_camera_color();
  void draw_camera_depth();
  void draw_camera_ir();

private:
  GUI* gui;
  GUI_stream* gui_stream;
  Kinect* kinect;
  Struct_kinect* struct_kinect;
};

#endif
