#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}


namespace velodyne{

class Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();

private:
  eng::Node* node_engine;
  //velodyne::Capture* velo_capture;
};

}
