#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace velodyne{class Node;}
namespace velodyne::structure{class Main;}


namespace velodyne::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(velodyne::Node* node_velodyne, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel();

  //Player function
  void draw_player();
  void player_slider();
  void player_start();
  void player_stop();
  void player_repeat();
  void player_close();
  void player_lock();

private:
  velodyne::structure::Main* velo_struct;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
