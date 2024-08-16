#pragma once

namespace dat::ply{class Node;}
namespace dat::ply{class Player;}
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
  dat::ply::Player* dyn_player;
  dyn::element::Sensor* dyn_sensor;
};

}
