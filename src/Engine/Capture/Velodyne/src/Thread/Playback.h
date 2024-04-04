#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}


namespace vld{

class Playback
{
public:
  //Constructor / Destructor
  Playback(vld::structure::Main* vld_struct);
  ~Playback();

public:
  //Main function

private:
  vld::structure::Main* vld_struct;
};

}
