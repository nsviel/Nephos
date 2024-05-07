#pragma once

#include <Dynamic/src/Playback/Device.h>
#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::processing{class Data;}
namespace k4n::utils{class Configuration;}
namespace k4n::structure{class K4N;}


namespace k4n::playback{

class Thread : public dyn::playback::Device
{
public:
  //Constructor / Destructor
  Thread(k4n::Node* node_k4n);
  ~Thread();

public:
  //Main function
  void thread_init(dat::base::Sensor* sensor);
  void thread_loop(dat::base::Sensor* sensor);
  void thread_end(dat::base::Sensor* sensor);

  //Subfunction
  k4a::capture* manage_new_capture(k4n::dev::Sensor* sensor);
  void manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture);
  void manage_pause(k4n::dev::Sensor* sensor);
  void manage_restart(k4n::dev::Sensor* sensor);

private:
  k4n::processing::Data* k4n_data;
  k4n::utils::Configuration* k4n_config;
};


}
