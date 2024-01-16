#pragma once

#include <Engine/Capture/K4N/Structure/Struct_swarm.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Scene/Data/Scene.h>
#include <Utility/Specific/common.h>

class Engine;

namespace k4n::dev{


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
  void close_sensor(k4n::dev::Sensor* device);
  void close_sensor_all();
  void selecte_next_sensor();

  inline k4n::dev::Sensor* get_selected_sensor(){return struct_swarm->selected_device;}
  inline list<k4n::dev::Sensor*>& get_list_sensor(){return struct_swarm->list_sensor;}
  inline int get_nb_dev_capture(){return struct_swarm->nb_dev_capture;}
  inline int get_nb_dev_playback(){return struct_swarm->nb_dev_playback;}
  inline void set_selected_device(k4n::dev::Sensor* device){struct_swarm->selected_device = device;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  k4n::structure::Swarm* struct_swarm;
  k4n::utils::Transformation* k4n_transfo;

  string default_folder;
  string default_file;
};

}
