#pragma once

#include <Utility/Specific/common.h>
#include <Utility/UTL_capture/UTL_kinect/Kinect.h>

class Kinect;


class UTL_capture
{
public:
  //Constructor / Destructor
  UTL_capture();
  ~UTL_capture();

public:
  //Main function
  void init();
  void run();
  void clean();

  inline Kinect* get_kinect(){return kinect;}

private:
  Kinect* kinect;
};
