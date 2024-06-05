#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Player;}
namespace k4n{class Node;}


namespace k4n::playback{

class Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n);
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
