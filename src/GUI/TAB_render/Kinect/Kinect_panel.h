#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/UTL_specific/common.h>
#include <GUI/TAB_render/Kinect/Namespace.h>

class GUI;
class Recorder;


namespace gui::kinect{

class Kinect_panel : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Kinect_panel(GUI* gui, bool* show_window, string name);
  ~Kinect_panel();

  //Main function
  void design_panel();

  //Subfunction
  void draw_tab_capture();
  void draw_tab_playback();
  void draw_tab_recorder();

private:
  gui::kinect::Configuration* kin_configuration;
  gui::kinect::Playback* kin_playback;
  gui::kinect::Recorder* kin_recorder;
};

}
