#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>


namespace gui::kinect{

class Player
{
public:
  //Constructor / Destructor
  Player(Engine* engine);
  ~Player();

  //Main function
  void draw_player();

  //Subfunction
  void player_control();
  void player_slider();

  //Player button
  void player_start();
  void player_stop();
  void player_repeat();
  void player_record();
  void player_close();

private:
  eng::scene::Scene* sce_scene;
  k4n::Node* node_kinect;
  k4n::utils::Player* k4a_player;
  k4n::truc::Swarm* k4a_swarm;
};

}
