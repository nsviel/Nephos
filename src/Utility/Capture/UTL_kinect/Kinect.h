#pragma once

#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <Utility/Capture/UTL_kinect/K4A_device/K4A_device.h>
#include <Utility/Specific/common.h>

class Struct_k4a_swarm;
class K4A_swarm;
class K4A_connection;


class Kinect
{
public:
  //Constructor / Destructor
  Kinect();
  ~Kinect();

public:
  //Main function
  void init();
  void restart_capture();

  inline K4A_swarm* get_k4a_swarm(){return k4a_swarm;}
  inline K4A_device* get_selected_device(){return struct_k4a_swarm->selected_device;}
  inline list<K4A_device*>& get_list_device(){return struct_k4a_swarm->list_device;}
  inline int get_nb_device_real(){return struct_k4a_swarm->nb_device_real;}
  inline int get_nb_device_virtual(){return struct_k4a_swarm->nb_device_virtual;}
  inline void set_selected_device(K4A_device* device){struct_k4a_swarm->selected_device = device;}

private:
  Struct_k4a_swarm* struct_k4a_swarm;
  K4A_swarm* k4a_swarm;
  K4A_connection* k4a_connection;
};
