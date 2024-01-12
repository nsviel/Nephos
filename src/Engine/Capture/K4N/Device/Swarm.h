#pragma once

#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Structure/Struct_swarm.h>
#include <Engine/Scene/Data/Scene.h>
#include <Utility/Specific/common.h>

class Engine;
class Swarm;
namespace k4n::device{
class Device;

class Swarm
{
public:
  //Constructor / Destructor
  Swarm(Engine* engine);
  ~Swarm();

public:
  //Main function
  void draw_all_clouds();
  void reset_all_device();

  //Connection function
  void refresh_connected_device();
  void manage_new_device(int number);
  void manage_less_device(int number);
  void manage_no_device();

  //Creation function
  k4n::device::Device* create_playback(string path);
  k4n::device::Device* create_device();
  void close_device(k4n::device::Device* device);
  void close_device_all();
  void selecte_next_device();

  inline k4n::device::Device* get_selected_device(){return struct_swarm->selected_device;}
  inline list<k4n::device::Device*>& get_list_device(){return struct_swarm->list_device;}
  inline int get_nb_device(){return struct_swarm->nb_device;}
  inline int get_nb_playback(){return struct_swarm->nb_playback;}
  inline void set_selected_device(k4n::device::Device* device){struct_swarm->selected_device = device;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  k4n::structure::Swarm* struct_swarm;

  string default_folder;
  string default_file;
};

}
