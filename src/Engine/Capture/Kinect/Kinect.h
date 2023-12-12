#pragma once

#include <Engine/Capture/Kinect/Structure/Namespace.h>
#include <Engine/Capture/Kinect/Thread/Namespace.h>
#include <Engine/Capture/Kinect/Namespace.h>
#include <Engine/Capture/Kinect/Device/K4A_swarm.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>

#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Engine;


namespace eng::kinect{

class Kinect
{
public:
  //Constructor / Destructor
  Kinect(Engine* engine);
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
  eng::kinect::structure::Swarm* struct_k4a_swarm;
  K4A_swarm* k4a_swarm;
  eng::kinect::thread::Connection* k4a_connection;
};

}
