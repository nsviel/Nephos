#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

namespace utl::fps{class Counter;}
namespace utl::fps{class Control;}
namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::data{class Data;}
namespace eng::k4n::data{class Cloud;}
namespace eng::k4n::data{class Image;}
namespace eng::k4n::config{class Configuration;}
namespace eng::k4n::config{class Calibration;}
namespace eng::k4n::utils{class Operation;}


namespace eng::k4n::thread{

class Playback
{
public:
  //Constructor / Destructor
  Playback(eng::k4n::Node* node_k4n);
  ~Playback();

public:
  //Main function
  void start_thread(eng::k4n::dev::Sensor* device);
  void run_thread(eng::k4n::dev::Sensor* device);
  void stop_thread();

  //Subfunction
  void manage_pause(eng::k4n::dev::Sensor* sensor);
  void manage_restart(eng::k4n::dev::Sensor* device);
  void manage_recording(eng::k4n::dev::Sensor* sensor, k4a::capture capture);

  inline bool is_thread_running(){return thread_running;}

private:
  utl::fps::Counter* fps_counter;
  utl::fps::Control* fps_control;
  eng::k4n::data::Data* k4a_data;
  eng::k4n::data::Cloud* k4a_cloud;
  eng::k4n::data::Image* k4n_image;
  eng::k4n::config::Configuration* k4n_configuration;
  eng::k4n::config::Calibration* k4n_calibration;
  eng::k4n::utils::Operation* k4n_operation;

  std::thread thread;
  bool thread_running = false;
};


}
