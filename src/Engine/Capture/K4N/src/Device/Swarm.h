#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Manager;}
namespace eng{class Node;}
namespace eng::scene{class Scene;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Transformation;}


namespace k4n::dev{

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(k4n::Node* node_k4n);
  ~Swarm();

public:
  //Main function
  void init_scene();

  //Sensor function
  void create_sensor_playback(utl::media::File& file);
  void create_sensor_capture();

  //Master function
  void close_all_master();
  void close_master(k4n::dev::Master* master);
  k4n::dev::Master* get_or_create_master(string name);
  k4n::dev::Master* get_master_by_name(string name);

  inline k4n::dev::Master* get_selected_master(){return selected_master;}
  inline list<k4n::dev::Master*>& get_list_master(){return list_master;}

private:
  prf::Manager* profiler;
  eng::scene::Scene* sce_scene;
  k4n::Node* node_k4n;
  k4n::utils::Transformation* k4n_transfo;

  k4n::dev::Master* selected_master = nullptr;
  std::list<k4n::dev::Master*> list_master;
};

}
