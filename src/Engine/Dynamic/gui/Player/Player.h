#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Graph;}
namespace dat::base{class Set;}
namespace dyn{class Node;}
namespace dyn::gui{class Control;}
namespace dyn::gui{class Operation;}


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
  void design_player(dat::base::Set* set);

  //Player function
  void player_slider(dat::base::Set* set);
  void player_start(dat::base::Set* set);
  void player_stop(dat::base::Set* set);
  void player_repeat(dat::base::Set* set);
  void player_record(dat::base::Set* set);
  void player_close(dat::base::Set* set);
  void player_lock(dat::base::Set* set);

private:
  dyn::gui::Control* gui_control;
  dyn::gui::Operation* gui_operation;
  dat::Graph* dat_graph;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
