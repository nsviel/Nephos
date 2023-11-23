#ifndef K4A_REPLAY_H
#define K4A_REPLAY_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>
#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class Struct_kinect;
class K4A_capture;
class K4A_device;


class K4A_replay
{
public:
  //Constructor / Destructor
  K4A_replay(Struct_kinect* struct_kinect);
  ~K4A_replay();

public:
  //Main function
  void run();

  //Subfunction
  void start_thread(Struct_k4a_device* device);
  void run_capture(Struct_k4a_device* device);
  void stop_thread();
  void sleep_necessary_time(Struct_k4a_device* device);

  inline bool is_thread_running(){return thread_running;}

private:
  Struct_kinect* struct_kinect;
  K4A_device* k4a_device;

  std::thread thread;
  bool thread_running = false;
};

#endif
