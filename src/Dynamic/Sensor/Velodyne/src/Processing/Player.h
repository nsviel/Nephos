#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}


namespace vld::processing{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::Node* node_velodyne);
  ~Player();

public:
  //Main function
  void player_pause(bool value);
  void player_play();
  void player_stop();
  void player_restart();
  void player_close();

  //Subfunction
  void determine_range();
  void compute_visibility();
  void forward_index(int index);

private:
  vld::Structure* vld_struct;
};

}
