#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Graph;}
namespace dyn{class Node;}
namespace dyn::gui{class Control;}
namespace dyn::base{class Player;}


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
  void draw_player(dyn::base::Player* ply);
  void player_slider(dyn::base::Player* ply);
  void player_start(dyn::base::Player* ply);
  void player_stop(dyn::base::Player* ply);
  void player_repeat(dyn::base::Player* ply);
  void player_record(dyn::base::Player* ply);
  void player_close(dyn::base::Player* ply);
  void player_lock(dyn::base::Player* ply);

  //Module function
  std::function<void()> info;

private:
  dyn::gui::Control* gui_control;
  dat::Graph* dat_graph;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
