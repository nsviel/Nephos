#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Namespace.h>


namespace eng::capture{

class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main function
  void init();
  void run();
  void clean();

  inline eng::kinect::Kinect* get_kinect(){return kinect;}

private:
  eng::kinect::Kinect* kinect;
};

}
