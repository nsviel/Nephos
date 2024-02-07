#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::data{class Data;}
namespace eng::k4n::data{class Cloud;}
namespace eng::k4n::config{class Configuration;}
namespace eng::k4n::config{class Calibration;}


namespace eng::k4n::thread{

class Capture
{
public:
  //Constructor / Destructor
  Capture(eng::k4n::Node* node_k4n);
  ~Capture();

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
  eng::k4n::data::Data* k4a_data;
  eng::k4n::data::Cloud* k4a_cloud;
  eng::k4n::config::Configuration* configuration;
  eng::k4n::config::Calibration* k4n_calibration;

  std::thread thread;
  bool thread_running = false;
  bool thread_pause = false;
  bool is_recording = false;
};


}
