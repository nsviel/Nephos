#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Graph;}
namespace dyn{class Node;}
namespace dyn::gui::player{class Control;}
namespace dyn::gui::player{class Structure;}


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
  void draw_player(dyn::gui::player::Structure* ply);
  void player_slider(dyn::gui::player::Structure* ply);
  void player_start(dyn::gui::player::Structure* ply);
  void player_stop(dyn::gui::player::Structure* ply);
  void player_repeat(dyn::gui::player::Structure* ply);
  void player_record(dyn::gui::player::Structure* ply);
  void player_close(dyn::gui::player::Structure* ply);
  void player_lock(dyn::gui::player::Structure* ply);

private:
  dyn::gui::player::Control* player_control;
  dat::Graph* dat_graph;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
