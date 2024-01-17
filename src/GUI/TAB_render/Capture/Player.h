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
  void draw_player(k4n::dev::Device* device);

  //Subfunction
  void player_control(k4n::dev::Device* device);
  void player_slider(k4n::dev::Device* device);

  //Player button
  void player_start(k4n::dev::Device* device);
  void player_stop(k4n::dev::Device* device);
  void player_repeat(k4n::dev::Device* device);
  void player_record(k4n::dev::Device* device);
  void player_close(k4n::dev::Device* device);

private:
  eng::scene::Scene* sce_scene;
  k4n::Node* node_kinect;
  k4n::dev::Swarm* k4n_swarm;
};

}
