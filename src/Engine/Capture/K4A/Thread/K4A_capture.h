#pragma once

#include <Engine/Capture/K4A/Thread/K4A_processing.h>
#include <Engine/Capture/K4A/Data/Namespace.h>
#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Engine/Capture/K4A/Utils/Namespace.h>
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
  K4A_capture(Engine* engine);
  ~K4A_capture();

public:
  //Main function
  void run();

  //Subfunction
  void start_thread(K4A_device* device);
  void run_thread(K4A_device* device);
  void stop_thread();
  void manage_pause(K4A_device* k4a_device);
  void manage_recording(K4A_device* k4a_device, k4a::capture capture);
  void manage_color_setting(K4A_device* k4a_device);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  FPS_counter* fps_counter;
  FPS_control* fps_control;
  eng::kinect::data::Data* k4a_data;
  K4A_processing* k4a_processing;
  eng::kinect::Configuration* k4a_config;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};
