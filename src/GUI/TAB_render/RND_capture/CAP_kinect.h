#ifndef GUI_KINECT_H
#define GUI_KINECT_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class Kinect;
class Struct_swarm;
class K4A_swarm;
class K4A_configuration;


class CAP_kinect : public BASE_panel
{
public:
  //Constructor / Destructor
  CAP_kinect(GUI* gui, bool* show_window, string name);
  ~CAP_kinect();

  //Main function
  void design_panel();

  //Kinect configuration
  void kinect_devices();
  void configuration_device();
  void configuration_depth();
  void configuration_color();
  void configuration_general();
  void firmware_info();

  void playback_stuff();
  void recorder_stuff();

private:
  Kinect* kinect;
  Struct_swarm* struct_swarm;
  K4A_swarm* k4a_swarm;
  K4A_configuration* k4a_configuration;

  bool show_capture = false;
};

#endif
