#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}


namespace vld{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::structure::Main* velo_struct);
  ~Player();

public:
  //Main function
  void determine_range();

private:
  vld::structure::Main* velo_struct;
};

}
