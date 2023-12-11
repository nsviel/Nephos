#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Capture/UTL_kinect/Kinect.h>

class Kinect;


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

  inline Kinect* get_kinect(){return kinect;}

private:
  Kinect* kinect;
};

}
