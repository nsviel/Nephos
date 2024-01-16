#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Structure/Struct_swarm.h>
#include <Engine/Scene/Data/Scene.h>
#include <Utility/Specific/common.h>

class Engine;

namespace k4n{


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
  void refresh_connected_device();
  void manage_new_capture_device(int number);
  void manage_less_capture_device(int number);

  //Creation function
  k4n::Device* create_device_playback(string path);
  k4n::Device* create_device_capture();
  void close_device(k4n::Device* device);
  void close_device_all();
  void selecte_next_device();

  inline k4n::Device* get_selected_device(){return struct_swarm->selected_device;}
  inline list<k4n::Device*>& get_list_device(){return struct_swarm->list_device;}
  inline int get_nb_device(){return struct_swarm->nb_device;}
  inline int get_nb_playback(){return struct_swarm->nb_playback;}
  inline void set_selected_device(k4n::Device* device){struct_swarm->selected_device = device;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  k4n::structure::Swarm* struct_swarm;
  k4n::utils::Transformation* k4n_transfo;

  string default_folder;
  string default_file;
};

}
