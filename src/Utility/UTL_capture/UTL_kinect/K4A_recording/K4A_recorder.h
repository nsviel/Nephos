#ifndef K4A_RECORDER_H
#define K4A_RECORDER_H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

class Struct_kinect;


class K4A_recorder
{
public:
  //Constructor / Destructor
  K4A_recorder(Struct_kinect* struct_kinect);
  ~K4A_recorder();

public:
  //Main function
  void record_mkv(string path);

private:
  Struct_kinect* struct_kinect;

};

#endif
