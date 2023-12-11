#pragma once

#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/Kinect.h>

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
