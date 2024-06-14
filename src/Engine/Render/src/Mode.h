#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}


namespace rnd{

class Mode
{
public:
  //Constructor / Destructor
  Mode(eng::Node* node_engine);
  ~Mode();

public:
  //Main function
  void mode_visualization();

private:

};

}
