#pragma once

#include <Utility/Capture/Kinect/Data/Namespace.h>
#include <Utility/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>


class K4A_capture
{
public:
  //Constructor / Destructor
  K4A_capture();
  ~K4A_capture();

public:
  //Main function
  void run();

  //Subfunction
  void start_thread(K4A_device* device);
  void run_thread(K4A_device* device);
  void stop_thread();

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  util::kinect::data::Data* k4a_data;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};
