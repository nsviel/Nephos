#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Capture/Namespace.h>

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
  void run_panel();
  void design_panel();

  //Subfunction
  void show_info();

private:
  gui::kinect::Capture* kin_capture;
  gui::kinect::Playback* kin_playback;
  gui::kinect::Recorder* kin_recorder;
  gui::kinect::Player* kin_player;
  gui::kinect::Operation* kin_operation;
  k4n::dev::Swarm* k4n_swarm;
};

}
