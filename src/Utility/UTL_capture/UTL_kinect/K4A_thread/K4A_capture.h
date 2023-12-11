#pragma once

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

class K4A_data;


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
  K4A_data* k4a_data;

  std::thread thread;
  bool thread_running = false;
  bool thread_recording = false;
  bool thread_pause = false;
};
