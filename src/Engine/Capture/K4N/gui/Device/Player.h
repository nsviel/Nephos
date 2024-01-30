#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Master;}
namespace eng::k4n::dev{class Swarm;}
namespace eng::scene{class Scene;}


namespace eng::k4n::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(eng::k4n::Node* node_k4n);
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
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
