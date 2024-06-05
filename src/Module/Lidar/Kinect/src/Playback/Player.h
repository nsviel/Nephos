#pragma once

#include <Dynamic/src/Player/Player.h>
#include <Utility/Specific/Common.h>

namespace dyn::base{class Player;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}


namespace k4n::playback{

class Player : public dyn::base::Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n, dat::base::Set* set);
  ~Player();

public:
  //Main function
  void manage_update();
  void manage_query(float value);
  void player_close();
  void player_stop();

public:

};

}
