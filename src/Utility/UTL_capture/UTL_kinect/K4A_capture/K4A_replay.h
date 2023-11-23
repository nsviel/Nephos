#ifndef K4A_REPLAY_H
#define K4A_REPLAY_H

#include <UTL_specific/common.h>

class Struct_kinect;
class K4A_capture;
class K4A_device;


class K4A_replay
{
public:
  //Constructor / Destructor
  K4A_replay();
  ~K4A_replay();

public:
  //Main function
  void run();

  //Subfunction
  void start_camera();

  inline K4A_capture* get_k4a_capture(){return k4a_capture;}
  inline K4A_device* get_k4a_device(){return k4a_device;}

private:
  Struct_kinect* struct_kinect;
  K4A_capture* k4a_capture;
  K4A_device* k4a_device;
};

#endif
