#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Namespace.h>

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
  void player_start();
  void player_stop();
  void player_repeat();
  void player_record();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;
};

}
