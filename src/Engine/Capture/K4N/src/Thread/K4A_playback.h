#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Engine/Capture/K4N/src/Data/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>
#include <Engine/Capture/K4N/src/Configuration/Namespace.h>
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
  void start_thread(k4n::src::dev::Sensor* device);
  void run_thread(k4n::src::dev::Sensor* device);
  void stop_thread();

  //Subfunction
  void manage_pause(k4n::src::dev::Sensor* sensor);
  void manage_restart(k4n::src::dev::Sensor* device);
  void manage_recording(k4n::src::dev::Sensor* sensor, k4a::capture capture);

  inline bool is_thread_running(){return thread_running;}

private:
  FPS_counter* fps_counter;
  FPS_control* fps_control;
  k4n::src::data::Data* k4a_data;
  k4n::src::data::Cloud* k4a_processing;
  k4n::src::config::Configuration* k4n_configuration;
  k4n::src::config::Calibration* k4n_calibration;
  k4n::src::utils::Operation* k4n_operation;

  std::thread thread;
  bool thread_running = false;
};
