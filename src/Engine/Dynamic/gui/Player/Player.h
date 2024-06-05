#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dat::base{class Set;}
namespace dyn{class Node;}
namespace dyn::gui{class Operation;}
namespace dyn::player{class Action;}


namespace dyn::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic, bool* show_window);
  ~Player();

  //Main function
  void run_panel();
  void design_panel();
  void design_player();

  //Player function
  void player_slider(dat::base::Set* set);
  void player_start();
  void player_stop();
  void player_repeat();
  void player_record();
  void player_close();
  void player_lock();

private:
  dyn::player::Action* dyn_player;
  dyn::gui::Operation* gui_operation;
  dat::Selection* dat_selection;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
