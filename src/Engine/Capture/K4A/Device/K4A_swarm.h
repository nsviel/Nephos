#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Engine/Capture/K4A/Structure/Namespace.h>
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
  void draw_all_clouds();
  void reset_all_device();

  //Connection function
  void refresh_connected_device();
  void manage_new_device(int number);
  void manage_less_device(int number);
  void manage_no_device();

  //Creation function
  K4A_device* create_playback(string path);
  K4A_device* create_device();
  void delete_device(K4A_device* device);
  void delete_device_all();
  void selecte_next_device();

  inline K4A_device* get_selected_device(){return str_swarm->selected_device;}
  inline list<K4A_device*>& get_list_device(){return str_swarm->list_device;}
  inline int get_nb_device(){return str_swarm->nb_device;}
  inline int get_nb_playback(){return str_swarm->nb_playback;}
  inline void set_selected_device(K4A_device* device){str_swarm->selected_device = device;}

private:
  Engine* engine;
  eng::kinect::structure::Swarm* str_swarm;

  string default_folder;
  string default_file;
};
