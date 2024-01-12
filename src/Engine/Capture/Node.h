#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class Engine;


namespace eng::capture{

class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();
  void reset();

  inline k4n::Node* get_node_kinect(){return node_kinect;}

private:
  k4n::Node* node_kinect;
};

}
