#ifndef GUI_CAPTURE_H
#define GUI_CAPTURE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;
class GUI_stream;
class Kinect;
class Struct_kinect;
class K4A_depth;
class K4A_infrared;


class CAP_capture : public BASE_panel
{
public:
  //Constructor / Destructor
  CAP_capture(GUI* gui, bool* show_window, string name);
  ~CAP_capture();

  //Main function
  void design_panel();

  //Subfunction
  void draw_camera_color(ImVec2 image_size);
  void draw_camera_depth(ImVec2 image_size);
  void draw_camera_ir(ImVec2 image_size);
  void hovered_info_panel(K4A_image* image);

private:
  GUI* gui;
  Kinect* kinect;
  Struct_kinect* struct_kinect;
  K4A_depth* k4a_depth;
  K4A_infrared* k4a_infrared;

  vector<GUI_stream*> vec_gui_stream;
};

#endif
