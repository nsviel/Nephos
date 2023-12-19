#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Namespace.h>
#include <Engine/Capture/K4A/Utils/Player.h>

class K4A_swarm;


namespace gui::kinect{

class Player
{
public:
  //Constructor / Destructor
  Player(eng::kinect::Kinect* kinect);
  ~Player();

  //Main function
  void draw_player();

  //Subfunction
  void player_control();
  void player_slider();

  //Player button
  void player_close();
  void player_start();
  void player_stop();
  void player_repeat();
  void player_record();

private:
  eng::kinect::Kinect* kinect;
  eng::kinect::Player* k4a_player;
  K4A_swarm* k4a_swarm;
};

}
