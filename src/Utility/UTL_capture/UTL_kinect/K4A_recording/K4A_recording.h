#ifndef K4A_RECORDING_H
#define K4A_RECORDING_H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class Struct_kinect;


class K4A_recording
{
public:
  //Constructor / Destructor
  K4A_recording(Struct_kinect* struct_kinect);
  ~K4A_recording();

public:
  //Main function
  void record_control(string path);

private:
  Struct_kinect* struct_kinect;

};

#endif
