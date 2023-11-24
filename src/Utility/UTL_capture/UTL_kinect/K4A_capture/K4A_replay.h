#ifndef K4A_REPLAY_H
#define K4A_REPLAY_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>
#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class K4A_data;


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
  void start_thread(K4A_device* device);
  void run_capture(K4A_device* device);
  void stop_thread();
  void sleep_necessary_time(K4A_device* device);

  inline bool is_thread_running(){return thread_running;}

private:
  K4A_data* k4a_data;

  std::thread thread;
  bool thread_running = false;
};

#endif
