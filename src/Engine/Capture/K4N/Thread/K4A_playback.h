#pragma once

#include <Engine/Capture/K4N/Data/Namespace.h>
#include <Engine/Capture/K4N/Device/K4A_device.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Capture/K4N/Configuration/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

class FPS_counter;
class FPS_control;
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
  void find_duration(K4A_device* k4a_device);
  void manage_fps(int fps_mode);
  void manage_query_ts(K4A_device* device);
  void manage_pause(K4A_device* k4a_device);
  void manage_restart(K4A_device* device);
  void manage_recording(K4A_device* k4a_device, k4a::capture capture);

  inline bool is_thread_running(){return thread_running;}

private:
  FPS_counter* fps_counter;
  FPS_control* fps_control;
  k4n::data::Data* k4a_data;
  k4n::data::Cloud* k4a_processing;
  k4n::config::Configuration* k4a_config;

  std::thread thread;
  bool thread_running = false;
};
