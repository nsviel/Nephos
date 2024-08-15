#pragma once

namespace dyn{class Node;}
namespace dat::ply{class Player;}
namespace dyn::element{class Sensor;}
namespace utl::base{class Element;}


namespace dat::ply::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic);
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
