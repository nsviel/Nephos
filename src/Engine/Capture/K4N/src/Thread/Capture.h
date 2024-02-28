#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::data{class Data;}
namespace k4n::data{class Cloud;}
namespace k4n::config{class Configuration;}
namespace k4n::config{class Calibration;}


namespace k4n::thread{

class Capture
{
public:
  //Constructor / Destructor
  Capture();
  ~Capture();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* device);
  void run_thread(k4n::dev::Sensor* device);
  void stop_thread();

  //Subfunction
  k4a::capture* manage_capture(k4n::dev::Sensor* sensor);
  void manage_pause(k4n::dev::Sensor* sensor);
  void manage_recording(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void manage_color_setting(k4n::dev::Sensor* sensor);

  inline bool is_thread_running(){return thread_running;}
  inline bool* get_thread_pause(){return &thread_pause;}

private:
  k4n::data::Data* k4a_data;
  k4n::data::Cloud* k4a_cloud;
  k4n::config::Configuration* configuration;
  k4n::config::Calibration* k4n_calibration;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};


}
