#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Graph;}
namespace dat::base{class Set;}
namespace dyn{class Node;}
namespace dyn::gui{class Control;}
namespace dyn::base{class Player;}
namespace ope{class Operation;}


namespace dyn::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel(dat::base::Set* set);

  //Player function
  void draw_player(dyn::base::Player* ply);
  void player_slider(dyn::base::Player* ply);
  void player_start(dyn::base::Player* ply);
  void player_stop(dyn::base::Player* ply);
  void player_repeat(dyn::base::Player* ply);
  void player_record(dyn::base::Player* ply);
  void player_close(dyn::base::Player* ply);
  void player_lock(dyn::base::Player* ply);
  void draw_button();

private:
  dyn::gui::Control* gui_control;
  dat::Graph* dat_graph;
  ope::Operation* ope_operation;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
