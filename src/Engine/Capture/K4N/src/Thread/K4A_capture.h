#pragma once

#include <Engine/Capture/K4N/src/Data/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>
#include <Engine/Capture/K4N/src/Configuration/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

class FPS_counter;
class FPS_control;
class Engine;


class K4A_capture
{
public:
  //Constructor / Destructor
  K4A_capture(eng::k4n::Node* k4n_node);
  ~K4A_capture();

public:
  //Main function
  void run();

  //Subfunction
  void start_thread(eng::k4n::dev::Sensor* device);
  void run_thread(eng::k4n::dev::Sensor* device);
  void stop_thread();
  void manage_pause(eng::k4n::dev::Sensor* sensor);
  void manage_recording(eng::k4n::dev::Sensor* sensor, k4a::capture capture);
  void manage_color_setting(eng::k4n::dev::Sensor* sensor);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  FPS_counter* fps_counter;
  FPS_control* fps_control;
  eng::k4n::data::Data* k4a_data;
  eng::k4n::data::Cloud* k4a_cloud;
  eng::k4n::config::Configuration* configuration;
  eng::k4n::config::Calibration* k4n_calibration;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};
