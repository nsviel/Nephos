#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::data{class Depth;}
namespace k4n::data{class Infrared;}
namespace k4n::config{class Configuration;}
namespace k4n::thread{class Pool;}
namespace ope::attribut{class Fitting;}


namespace k4n::processing{

class Image
{
public:
  //Constructor / Destructor
  Image(k4n::Node* node_k4n);
  ~Image();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void copy_image_color(k4n::dev::Sensor* sensor);
  void copy_image_depth(k4n::dev::Sensor* sensor);
  void copy_image_ir(k4n::dev::Sensor* sensor);

private:
  k4n::thread::Pool* thread_pool;
  k4n::data::Depth* k4n_depth;
  k4n::data::Infrared* k4n_infrared;
  k4n::config::Configuration* k4n_config;
  ope::attribut::Fitting* ope_fitting;

  bool idle = true;
};

}
