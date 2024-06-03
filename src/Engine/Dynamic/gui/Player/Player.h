#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dat::base{class Set;}
namespace dyn{class Node;}
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
  void design_panel();
  void design_player();

  //Player function
  void player_slider(dat::base::Set* set);
  void player_start(dat::base::Set* set);
  void player_stop(dat::base::Set* set);
  void player_repeat(dat::base::Set* set);
  void player_record(dat::base::Set* set);
  void player_close(dat::base::Set* set);
  void player_lock(dat::base::Set* set);

private:
  dyn::gui::Operation* gui_operation;
  dat::Selection* dat_selection;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
