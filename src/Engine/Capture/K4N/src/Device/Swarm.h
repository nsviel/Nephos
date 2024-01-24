#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace eng::k4n::dev{
class Master;
class Node;


class Swarm
{
public:
  //Constructor / Destructor
  Swarm(eng::k4n::Node* k4n_node);
  ~Swarm();

public:
  //Main function
  void init_scene();

  //Sensor function
  void create_sensor_playback(utl::media::File& file);
  void create_sensor_capture();
  void close_sensor_all(eng::k4n::dev::Master* master);
  void close_selected_sensor();
  void selecte_next_sensor();

  //Master function
  eng::k4n::dev::Master* get_or_create_master(string name);
  eng::k4n::dev::Master* get_master_by_name(string name);

  inline eng::k4n::dev::Sensor* get_selected_sensor(){return selected_sensor;}
  inline eng::k4n::dev::Master* get_selected_master(){return selected_master;}
  inline list<eng::k4n::dev::Master*>& get_list_master(){return list_master;}
  inline void set_selected_sensor(eng::k4n::dev::Sensor* sensor){this->selected_sensor = sensor;}
  inline bool is_selected_sensor(eng::k4n::dev::Sensor* sensor){return selected_sensor == sensor;}

private:
  eng::k4n::Node* k4n_node;
  eng::scene::Scene* sce_scene;
  eng::k4n::utils::Transformation* k4n_transfo;

  eng::k4n::dev::Sensor* selected_sensor = nullptr;
  eng::k4n::dev::Master* selected_master = nullptr;
  std::list<eng::k4n::dev::Master*> list_master;
};

}
