#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>


namespace eng::k4n::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(eng::k4n::Node* k4n_node);
  ~Player();

  //Main function
  void draw_player(eng::k4n::dev::Master* master);

  //Subfunction
  void player_control(eng::k4n::dev::Master* master);
  void player_slider(eng::k4n::dev::Master* master);

  //Player button
  void player_start(eng::k4n::dev::Master* master);
  void player_stop(eng::k4n::dev::Master* master);
  void player_repeat(eng::k4n::dev::Master* master);
  void player_record(eng::k4n::dev::Master* master);
  void player_close(eng::k4n::dev::Master* master);
  void player_lock(eng::k4n::dev::Master* master);

private:
  eng::scene::Scene* sce_scene;
  eng::k4n::Node* k4a_node;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
