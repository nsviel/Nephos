#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::gui{class Capture;}
namespace eng::k4n::gui{class Playback;}
namespace eng::k4n::gui{class Recorder;}
namespace eng::k4n::gui{class Player;}
namespace eng::k4n::gui{class Master;}
namespace eng::k4n::gui{class Sensor;}
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Master;}
namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::gui{

class Device
{
public:
  //Constructor / Destructor
  Device(eng::k4n::Node* node_k4n, bool* show_window);
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
