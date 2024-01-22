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
  void show_info_master(k4n::dev::Master* master);
  void show_info_sensor(k4n::dev::Sensor* sensor);

private:
  gui::kinect::Capture* gui_capture;
  gui::kinect::Playback* gui_playback;
  gui::kinect::Recorder* gui_recorder;
  gui::kinect::Player* gui_player;
  gui::kinect::Master* gui_master;
  k4n::dev::Swarm* k4n_swarm;
  k4n::utils::Transformation* k4n_transfo;

  string open_tab = "";
};

}
