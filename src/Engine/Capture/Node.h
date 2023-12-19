#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Namespace.h>

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

  inline eng::kinect::Kinect* get_kinect(){return kinect;}

private:
  eng::kinect::Kinect* kinect;
};

}
