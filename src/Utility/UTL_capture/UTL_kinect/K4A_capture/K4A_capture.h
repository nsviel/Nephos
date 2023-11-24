#ifndef K4A_CAPTURE_H
#define K4A_CAPTURE_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>
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
  void start_thread(Struct_k4a_device* device);
  void run_capture(Struct_k4a_device* device);
  void stop_thread();

  inline bool is_thread_running(){return thread_running;}

private:
  K4A_data* k4a_data;

  std::thread thread;
  bool thread_running = false;
  bool thread_recording = false;
};


#endif
