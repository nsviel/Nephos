#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Manager;}
namespace eng{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Set;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Transformation;}
namespace k4n::structure{class Struct_k4n;}
namespace k4n::config{class Configuration;}


namespace k4n::dev{

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(k4n::structure::Struct_k4n* struct_k4n);
  ~Swarm();

public:
  //Sensor function
  void create_sensor_playback(utl::file::Path path);
  void create_sensor_capture(string serial_number, int index);

  //Master function
  void manage_resynchronization();
  void close_all_master();
  void close_master(string name);
  void close_master(k4n::dev::Master* master);
  int get_number_running_thread();
  k4n::dev::Master* get_or_create_playback_master(string name);
  k4n::dev::Master* get_or_create_capture_master(string name);
  k4n::dev::Master* get_master_by_name(string name);
  k4n::dev::Master* get_selected_master();

private:
  prf::Manager* profiler;
  eng::scene::Database* sce_database;
  eng::scene::Set* sce_set;
  k4n::utils::Transformation* k4n_transfo;
  k4n::structure::Struct_k4n* struct_k4n;
  k4n::config::Configuration* k4n_config;
};

}
