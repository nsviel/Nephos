#ifndef K4A_DEPTH_H
#define K4A_DEPTH_H

#include <UTL_specific/common.h>

class Struct_kinect;


class K4A_depth
{
public:
  //Constructor / Destructor
  K4A_depth();
  ~K4A_depth();

public:
  //Main function
  void find_depth_mode_range();

private:
  Struct_kinect* struct_kinect;
};

#endif
