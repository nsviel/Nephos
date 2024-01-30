#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Master;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::utils{class Transformation;}


namespace eng::k4n::dev{

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(eng::k4n::Node* node_k4n);
  ~Swarm();

public:
  //Main function
  void init_scene();

  //Sensor function
  void create_sensor_playback(utl::media::File& file);
  void create_sensor_capture();

  //Master function
  void close_master(eng::k4n::dev::Master* master);
  eng::k4n::dev::Master* get_or_create_master(string name);
  eng::k4n::dev::Master* get_master_by_name(string name);

  inline eng::k4n::dev::Master* get_selected_master(){return selected_master;}
  inline list<eng::k4n::dev::Master*>& get_list_master(){return list_master;}

private:
  eng::k4n::Node* node_k4n;
  eng::scene::Scene* sce_scene;
  eng::k4n::utils::Transformation* k4n_transfo;

  eng::k4n::dev::Master* selected_master = nullptr;
  std::list<eng::k4n::dev::Master*> list_master;
};

}
