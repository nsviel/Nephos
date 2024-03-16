#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::processing{class Data;}
namespace k4n::config{class Configuration;}
namespace k4n::config{class Calibration;}
namespace k4n::structure{class Struct_k4n;}


namespace k4n::thread{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::structure::Struct_k4n* struct_k4n);
  ~Capture();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* device);
  void run_thread(k4n::dev::Sensor* device);
  void stop_thread();
  void wait_thread();

  //Subfunction
  k4a::capture* manage_new_capture(k4n::dev::Sensor* sensor);
  void manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void manage_pause(k4n::dev::Sensor* sensor);
  void manage_recording(k4n::dev::Sensor* sensor);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  k4n::processing::Data* k4a_data;
  k4n::config::Configuration* k4n_config;
  k4n::config::Calibration* k4n_calibration;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool thread_idle = true;
  bool is_recording = false;
};


}
