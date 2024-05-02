#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Graph;}
namespace dyn{class Node;}
namespace dyn::gui{class Control;}
namespace dyn::player{class Structure;}


namespace dyn::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel(utl::type::Element* element);

  //Player function
  void draw_player(dyn::player::Structure* ply);
  void player_slider(dyn::player::Structure* ply);
  void player_start(dyn::player::Structure* ply);
  void player_stop(dyn::player::Structure* ply);
  void player_repeat(dyn::player::Structure* ply);
  void player_record(dyn::player::Structure* ply);
  void player_close(dyn::player::Structure* ply);
  void player_lock(dyn::player::Structure* ply);

private:
  dyn::gui::Control* gui_control;
  dyn::player::Structure* dyn_struct;
  dat::Graph* dat_graph;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
