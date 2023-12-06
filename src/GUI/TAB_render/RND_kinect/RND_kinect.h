#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class KIN_configuration;
class KIN_playback;
class KIN_recorder;


class RND_kinect : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_kinect(GUI* gui, bool* show_window, string name);
  ~RND_kinect();

  //Main function
  void design_panel();

  //Subfunction
  void draw_tab_capture();
  void draw_tab_playback();
  void draw_tab_recorder();

private:
  KIN_configuration* kin_configuration;
  KIN_playback* kin_playback;
  KIN_recorder* kin_recorder;
};
