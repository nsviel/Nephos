#pragma once

#include <Utility/Specific/Common.h>

namespace gui::player{class Control;}
namespace gui::player{class Structure;}


namespace gui::element{

class Player
{
public:
  //Constructor / Destructor
  Player(bool* show_window);
  ~Player();

  //Main function
  void draw_player(gui::player::Structure* ply);

  //Player function
  void player_slider(gui::player::Structure* ply);
  void player_start(gui::player::Structure* ply);
  void player_stop(gui::player::Structure* ply);
  void player_repeat(gui::player::Structure* ply);
  void player_record(gui::player::Structure* ply);
  void player_close(gui::player::Structure* ply);
  void player_lock(gui::player::Structure* ply);

private:
  gui::player::Control* player_control;

  bool* show_window;
  string name;
  string open_tab = "";
};

}
