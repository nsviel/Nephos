#pragma once

#include <Utility/Capture/Kinect/Data/Namespace.h>
#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/Kinect/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>


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
  void manage_current_timestamp(k4a::playback* playback, K4A_device* device, k4a::capture capture);
  void manage_pause();
  void manage_restart(k4a::playback* playback, K4A_device* device);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}
  inline bool* get_thread_restart(){return &thread_restart;}
  inline bool* get_thread_play(){return &thread_play;}
  inline void set_current_timestamp(float value){this->ts_seek = value;}

private:
  util::kinect::data::Data* k4a_data;

  std::thread thread;
  float ts_seek = -1;
  bool thread_running = false;
  bool thread_play = false;
  bool thread_pause = false;
  bool thread_restart = true;
};
