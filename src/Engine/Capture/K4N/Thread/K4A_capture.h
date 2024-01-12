#pragma once

#include <Engine/Capture/K4N/Data/Namespace.h>
#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Capture/K4N/Configuration/Namespace.h>
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
  void start_thread(k4n::truc::K4A_device* device);
  void run_thread(k4n::truc::K4A_device* device);
  void stop_thread();
  void manage_pause(k4n::truc::K4A_device* k4a_device);
  void manage_recording(k4n::truc::K4A_device* k4a_device, k4a::capture capture);
  void manage_color_setting(k4n::truc::K4A_device* k4a_device);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  FPS_counter* fps_counter;
  FPS_control* fps_control;
  k4n::data::Data* k4a_data;
  k4n::data::Cloud* k4a_processing;
  k4n::config::Configuration* k4a_config;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};
