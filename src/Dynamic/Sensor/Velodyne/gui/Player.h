#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::processing{class Player;}


namespace vld::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::Node* node_velodyne);
  ~Player();

public:
  //Main function
  void design_player();

  //Subfunction
  void player_slider();
  void player_start();
  void player_stop();
  void player_repeat();
  void player_close();
  void player_lock();

private:
  vld::Structure* vld_struct;
  vld::processing::Player* vld_player;
};

}
