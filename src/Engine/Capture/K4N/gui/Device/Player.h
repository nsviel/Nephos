#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>


namespace gui::kinect{

class Player
{
public:
  //Constructor / Destructor
  Player(Engine* engine);
  ~Player();

  //Main function
  void draw_player(k4n::src::dev::Master* master);

  //Subfunction
  void player_control(k4n::src::dev::Master* master);
  void player_slider(k4n::src::dev::Master* master);

  //Player button
  void player_start(k4n::src::dev::Master* master);
  void player_stop(k4n::src::dev::Master* master);
  void player_repeat(k4n::src::dev::Master* master);
  void player_record(k4n::src::dev::Master* master);
  void player_close(k4n::src::dev::Master* master);
  void player_lock(k4n::src::dev::Master* master);

private:
  eng::scene::Scene* sce_scene;
  k4n::Node* node_kinect;
  k4n::src::dev::Swarm* k4n_swarm;
};

}
