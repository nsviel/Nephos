#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}


namespace vld{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::structure::Main* vld_struct);
  ~Player();

public:
  //Main function
  void start_playback();
  void stop_playback();
  void determine_range();
  void compute_visibility();
  void forward_index(int index);

private:
  vld::structure::Main* vld_struct;
};

}
