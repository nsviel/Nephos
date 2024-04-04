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
  void determine_range();
  void compute_visibility();
  
private:
  vld::structure::Main* vld_struct;
};

}
