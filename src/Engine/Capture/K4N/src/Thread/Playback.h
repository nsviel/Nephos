#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::processing{class Data;}
namespace k4n::config{class Configuration;}
namespace k4n::config{class Calibration;}
namespace k4n::utils{class Operation;}
namespace k4n::structure{class Struct_k4n;}


namespace k4n::thread{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void stop_thread();
  void wait_thread();

  //Subfunction
  k4a::capture* manage_new_capture(k4n::dev::Sensor* sensor);
  void manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void manage_pause(k4n::dev::Sensor* sensor);
  void manage_restart(k4n::dev::Sensor* sensor);

  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

private:
  k4n::processing::Data* k4n_data;
  k4n::config::Configuration* k4n_configuration;
  k4n::config::Calibration* k4n_calibration;
  k4n::utils::Operation* k4n_operation;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};


}
