#pragma once

#include <memory>

namespace dat::ply{class Node;}
namespace dat::ply{class Button;}
namespace dat::ply{class State;}
namespace dat::ply{class Structure;}
namespace utl::base{class Element;}


namespace dat::ply::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dat::ply::Node* node_player);
  ~Player();

  //Main function
  void design_player(std::shared_ptr<utl::base::Element> element);

  //Player function
  void player_slider();
  void player_play();
  void player_stop();
  void player_repeat();
  void player_record();
  void player_close();
  void player_lock();

private:
  dat::ply::Structure* ply_struct;
  dat::ply::Button* ply_button;
  dat::ply::State* ply_state;
};

}
