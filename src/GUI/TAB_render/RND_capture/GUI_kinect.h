#ifndef GUI_KINECT_H
#define GUI_KINECT_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class GUI_stream;
class Kinect;
class Struct_kinect;
class K4A_device;


class GUI_kinect : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_kinect(GUI* gui, bool* show_window, string name);
  ~GUI_kinect();

  //Main function
  void design_panel();

  //Kinect configuration
  void kinect_devices();
  void configuration_device();
  void configuration_depth();
  void configuration_color();
  void configuration_general();
  void draw_camera_color();

private:
  GUI* gui;
  GUI_stream* gui_stream;
  Kinect* kinect;
  Struct_kinect* struct_kinect;
  K4A_device* k4a_device;

  bool show_capture = false;
};

#endif
