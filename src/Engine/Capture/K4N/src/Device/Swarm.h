#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace k4n::dev{
class Master;


class Swarm
{
public:
  //Constructor / Destructor
  Swarm(Engine* engine);
  ~Swarm();

public:
  //Main function
  void init_scene();

  //Sensor function
  void create_sensor_playback(utl::media::File& file);
  void create_sensor_capture();
  void close_sensor_all(k4n::dev::Master* master);
  void selecte_next_sensor();

  //Master function
  k4n::dev::Master* get_or_create_master(string name);
  k4n::dev::Master* get_master_by_name(string name);

  inline k4n::dev::Sensor* get_selected_sensor(){return selected_sensor;}
  inline k4n::dev::Master* get_selected_master(){return selected_master;}
  inline list<k4n::dev::Master*>& get_list_master(){return list_master;}
  inline void set_selected_sensor(k4n::dev::Sensor* sensor){this->selected_sensor = sensor;}
  inline bool is_selected_sensor(k4n::dev::Sensor* sensor){return selected_sensor == sensor;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  k4n::utils::Transformation* k4n_transfo;

  k4n::dev::Sensor* selected_sensor = nullptr;
  k4n::dev::Master* selected_master = nullptr;
  std::list<k4n::dev::Master*> list_master;
};

}
