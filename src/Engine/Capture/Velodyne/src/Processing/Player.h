#pragma once

#include <Utility/Specific/Common.h>

namespace velodyne::structure{class Main;}


namespace velodyne{

class Player
{
public:
  //Constructor / Destructor
  Player(velodyne::structure::Main* velo_struct);
  ~Player();

public:
  //Main function
  void determine_range();

private:
  velodyne::structure::Main* velo_struct;
};

}
