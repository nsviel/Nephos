#pragma once

#include <Engine/Capture/Kinect/Data/Namespace.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Engine/Capture/Kinect/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class FPS_counter;
class Engine;


class K4A_playback
{
public:
  //Constructor / Destructor
  K4A_playback(Engine* engine);
  ~K4A_playback();

public:
  //Main function
  void start_thread(K4A_device* device);
  void run_thread(K4A_device* device);
  void stop_thread();

  //Subfunction
  void sleep_necessary_time(int fps_mode);
  void find_duration(K4A_device* k4a_device);
  void forward_timestamp(K4A_device* device);
  void manage_timestamp(K4A_device* device);
  void manage_pause();
  void manage_restart(K4A_device* device);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}
  inline bool* get_thread_restart(){return &thread_restart;}
  inline bool* get_thread_play(){return &thread_play;}
  inline void set_current_timestamp(float value){this->ts_seek = value;}

private:
  FPS_counter* fps_counter;
  eng::kinect::data::Data* k4a_data;
  eng::kinect::data::Cloud* k4a_cloud;

  std::thread thread;
  float ts_seek = -1;
  bool thread_running = false;
  bool thread_play = false;
  bool thread_pause = false;
  bool thread_restart = true;
};
