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
  void start_thread(K4A_device* device);
  void run_thread(K4A_device* device);
  void stop_thread();

  //Subfunction
  void sleep_necessary_time(K4A_device* device);
  void find_file_info(K4A_device* device);
  void manage_current_timestamp(K4A_device* device, k4a::capture capture);
  void manage_thread_pause();

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}
  inline bool* get_thread_restart(){return &thread_restart;}
  inline void set_current_timestamp(float value){this->ts_seek = value;}

private:
  K4A_data* k4a_data;

  std::thread thread;
  float ts_seek = -1;
  bool thread_running = false;
  bool thread_pause = false;
  bool thread_restart = false;
};

#endif
