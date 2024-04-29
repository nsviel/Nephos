#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Manager;}
namespace eng{class Node;}
namespace dat{class Database;}
namespace dat{class Set;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Transformation;}
namespace k4n::structure{class K4N;}
namespace k4n::config{class Configuration;}


namespace k4n::dev{

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(k4n::Node* node_k4n);
  ~Swarm();

public:
  //Sensor function
  void create_sensor_playback(utl::Path path);
  void create_sensor_capture(int index);

  //Master function
  void close_all_master();
  void close_master(string name);
  void close_master(k4n::dev::Master* master);
  int get_number_running_thread();
  k4n::dev::Master* get_or_create_playback_master(string name);
  k4n::dev::Master* get_or_create_capture_master(string name);
  k4n::dev::Master* get_master_by_name(string name);
  k4n::dev::Master* get_selected_master();

  //Subfunction
  void manage_resynchronization();
  void manage_connected_device();

private:
  prf::Manager* profiler;
  dat::Database* dat_database;
  dat::Set* dat_set;
  k4n::Node* node_k4n;
  k4n::utils::Transformation* k4n_transfo;
  k4n::structure::K4N* k4n_struct;
  k4n::config::Configuration* k4n_config;
};

}
