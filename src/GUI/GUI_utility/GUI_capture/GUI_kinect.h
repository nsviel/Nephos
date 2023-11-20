#ifndef GUI_KINECT_H
#define GUI_KINECT_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
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

  //Subfunction
  void kinect_devices();
  void kinect_configuration();

private:
  GUI* gui;
  Kinect* kinect;
  Struct_kinect* struct_kinect;
  K4A_device* k4a_device;

};

#endif
