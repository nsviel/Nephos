#pragma once

#include <GUI_utility/Base_nsp.h>
#include <UTL_specific/common.h>
#include <TAB_render/Kinect_nsp.h>

class GUI;
class Recorder;


namespace gui::rnd::panel{

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
