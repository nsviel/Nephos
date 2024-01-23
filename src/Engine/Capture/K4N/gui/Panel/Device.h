#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/gui/Namespace.h>

class Engine;
class Recorder;


namespace gui::kinect{

class Device
{
public:
  //Constructor / Destructor
  Device(Engine* engine, bool* show_window, string name);
  ~Device();

  //Main function
  void run_panel();
  void design_panel();

  //Tab function
  void show_master_tab(k4n::src::dev::Master* master);
  void show_sensor_tab(k4n::src::dev::Sensor* sensor);

  //Subfunction
  ImGuiTabItemFlags get_tab_flag(k4n::src::dev::Sensor* sensor);

private:
  gui::kinect::Capture* gui_capture;
  gui::kinect::Playback* gui_playback;
  gui::kinect::Recorder* gui_recorder;
  gui::kinect::Player* gui_player;
  gui::kinect::Master* gui_master;
  gui::kinect::Sensor* gui_sensor;
  k4n::src::dev::Swarm* k4n_swarm;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
