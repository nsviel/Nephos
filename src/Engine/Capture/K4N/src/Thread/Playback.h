#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::data{class Data;}
namespace k4n::data{class Image;}
namespace k4n::config{class Configuration;}
namespace k4n::config{class Calibration;}
namespace k4n::utils{class Operation;}


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

  //Subfunction
  void manage_pause(k4n::dev::Sensor* sensor);
  void manage_restart(k4n::dev::Sensor* sensor);
  void manage_recording(k4n::dev::Sensor* sensor, k4a::capture capture);

  inline bool is_thread_running(){return thread_running;}

private:
  k4n::data::Data* k4a_data;
  k4n::data::Image* k4n_image;
  k4n::config::Configuration* k4n_configuration;
  k4n::config::Calibration* k4n_calibration;
  k4n::utils::Operation* k4n_operation;

  std::thread thread;
  bool thread_running = false;
};


}
