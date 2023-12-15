#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Kinect/Namespace.h>
#include <Engine/Capture/Kinect/Structure/Namespace.h>

class GUI;
class Recorder;


namespace gui::kinect{

class Panel : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Panel(GUI* gui, bool* show_window, string name);
  ~Panel();

  //Main function
  void design_panel();

  //Subfunction

private:
  gui::kinect::Capture* kin_capture;
  gui::kinect::Playback* kin_playback;
  gui::kinect::Recorder* kin_recorder;
  gui::kinect::Player* kin_player;
};

}
