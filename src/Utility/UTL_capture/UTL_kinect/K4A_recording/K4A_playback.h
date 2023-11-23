#ifndef K4A_PLAYBACK__H
#define K4A_PLAYBACK__H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class Struct_kinect;


class K4A_playback
{
public:
  //Constructor / Destructor
  K4A_playback(Struct_kinect* struct_kinect);
  ~K4A_playback();

public:
  //Main function
  void record_control(string path);

private:
  Struct_kinect* struct_kinect;

};

#endif
