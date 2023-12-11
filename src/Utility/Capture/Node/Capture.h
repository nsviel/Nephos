#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Capture/Kinect/Namespace.h>


namespace util::capture{

class Capture
{
public:
  //Constructor / Destructor
  Capture();
  ~Capture();

public:
  //Main function
  void init();
  void run();
  void clean();

  inline util::kinect::Kinect* get_kinect(){return kinect;}

private:
  util::kinect::Kinect* kinect;
};

}
