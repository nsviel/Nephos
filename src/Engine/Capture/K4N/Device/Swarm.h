#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Scene/Data/Scene.h>
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
  void draw_all_clouds();
  void init_scene();

  //Connection function
  void refresh_connected_sensor();
  void manage_new_capture_sensor(int number);
  void manage_less_capture_sensor(int number);

  //Creation / supression function
  k4n::dev::Sensor* create_sensor_playback(string path);
  k4n::dev::Sensor* create_sensor_capture();
  void close_sensor(k4n::dev::Sensor* device, k4n::dev::Master* master);
  void close_sensor_all();
  void selecte_next_sensor();

  inline k4n::dev::Sensor* get_selected_sensor(){return selected_sensor;}
  inline k4n::dev::Master* get_selected_master(){return selected_master;}
  inline list<k4n::dev::Master*>& get_list_master(){return list_master;}
  inline void set_selected_sensor(k4n::dev::Sensor* sensor){selected_sensor = sensor;}
  inline void set_selected_master(k4n::dev::Master* master){selected_master = master;}

  inline int get_nb_dev_capture(){return nb_dev_capture;}
  inline int get_nb_dev_playback(){return nb_dev_playback;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  k4n::utils::Transformation* k4n_transfo;

  k4n::dev::Sensor* selected_sensor = nullptr;
  k4n::dev::Master* selected_master = nullptr;
  std::list<k4n::dev::Master*> list_master;

  int nb_dev = 0;
  int nb_dev_capture = 0;
  int nb_dev_playback = 0;

};

}
