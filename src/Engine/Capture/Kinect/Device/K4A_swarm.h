#pragma once

#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Engine/Capture/Kinect/Structure/Namespace.h>
#include <Engine/Capture/Kinect/Device/Configuration.h>
#include <Utility/Specific/common.h>

class Engine;


class K4A_swarm
{
public:
  //Constructor / Destructor
  K4A_swarm(Engine* engine);
  ~K4A_swarm();

public:
  //Main function
  K4A_device* create_playback(string path);
  K4A_device* create_device(int index);
  void delete_device(K4A_device* device);
  void refresh_connected_device_list();
  void draw_all_clouds();

  inline K4A_device* get_selected_device(){return str_swarm->selected_device;}
  inline list<K4A_device*>& get_list_device(){return str_swarm->list_device;}
  inline int get_nb_device(){return str_swarm->nb_device;}
  inline int get_nb_playback(){return str_swarm->nb_playback;}
  inline void set_selected_device(K4A_device* device){str_swarm->selected_device = device;}

private:
  Engine* engine;
  eng::kinect::structure::Swarm* str_swarm;

  int ID_virtual = 0;
  int nb_connected_device = -1;
};
