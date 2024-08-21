#pragma once

namespace dat::ply{class Node;}
namespace dat::ply{class Button;}
namespace dat::ply{class State;}
namespace dyn::prc::element{class Sensor;}
namespace utl::base{class Element;}


namespace dat::ply::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dat::ply::Node* node_player);
  ~Player();

  //Main function
  void design_player(utl::base::Element* element);

  //Player function
  void player_slider();
  void player_play();
  void player_stop();
  void player_repeat();
  void player_record();
  void player_close();
  void player_lock();

private:
  dat::ply::Button* ply_button;
  dat::ply::State* ply_state;
  dyn::prc::element::Sensor* dyn_sensor;
};

}
