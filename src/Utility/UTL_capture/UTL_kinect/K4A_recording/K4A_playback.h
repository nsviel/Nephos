#ifndef K4A_PLAYBACK__H
#define K4A_PLAYBACK__H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>

class Struct_kinect;
class K4A_device;


class K4A_playback
{
public:
  //Constructor / Destructor
  K4A_playback(Struct_kinect* struct_kinect);
  ~K4A_playback();

public:
  //Main function
  void record_control(string path);

  inline Struct_k4a_info& get_struct_record(){return struct_info;}

private:
  K4A_device* k4a_device;
  Struct_kinect* struct_kinect;
  Struct_k4a_info struct_info;
};

#endif
