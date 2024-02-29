#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Set;}
namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::gui{class Capture;}
namespace k4n::gui{class Playback;}
namespace k4n::gui{class Recorder;}
namespace k4n::gui{class Master;}
namespace k4n::gui{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}


namespace k4n::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Player function
  void draw_player(k4n::dev::Master* master);
  void player_slider(k4n::dev::Master* master);
  void player_start(k4n::dev::Master* master);
  void player_stop(k4n::dev::Master* master);
  void player_repeat(k4n::dev::Master* master);
  void player_record(k4n::dev::Master* master);
  void player_close(k4n::dev::Master* master);
  void player_lock(k4n::dev::Master* master);

  //Device function
  void show_master_tab(k4n::dev::Master* master);
  void show_sensor_tab(k4n::dev::Sensor* sensor);

  //Subfunction
  ImGuiTabItemFlags get_tab_flag(k4n::dev::Sensor* sensor);

private:
  eng::scene::Set* sce_set;
  
  k4n::Node* node_k4n;
  k4n::gui::Capture* gui_capture;
  k4n::gui::Playback* gui_playback;
  k4n::gui::Recorder* gui_recorder;
  k4n::gui::Master* gui_master;
  k4n::gui::Sensor* gui_sensor;
  k4n::dev::Swarm* k4n_swarm;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
