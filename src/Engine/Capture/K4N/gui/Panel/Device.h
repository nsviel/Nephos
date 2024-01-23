#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/gui/Namespace.h>

class Engine;
class Recorder;


namespace eng::k4n::gui{

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
  void show_master_tab(eng::k4n::dev::Master* master);
  void show_sensor_tab(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  ImGuiTabItemFlags get_tab_flag(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::gui::Capture* gui_capture;
  eng::k4n::gui::Playback* gui_playback;
  eng::k4n::gui::Recorder* gui_recorder;
  eng::k4n::gui::Player* gui_player;
  eng::k4n::gui::Master* gui_master;
  eng::k4n::gui::Sensor* gui_sensor;
  eng::k4n::dev::Swarm* k4n_swarm;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
