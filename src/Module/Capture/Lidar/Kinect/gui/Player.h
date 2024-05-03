#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::gui{class Master;}
namespace k4n::gui{class Sensor;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace dyn::gui{class Player;}
namespace dat{class Graph;}


namespace k4n::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel(utl::type::Element* element);

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

private:
  k4n::gui::Master* gui_master;
  k4n::gui::Sensor* gui_sensor;
  k4n::dev::Swarm* k4n_swarm;
  dyn::gui::Player* dyn_player;
  dat::Graph* dat_graph;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
