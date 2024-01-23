#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


namespace gui::kinect{

class Master
{
public:
  //Constructor / Destructor
  Master(k4n::Node* node_kinect);
  ~Master();

  //Main function
  void show_master_info(k4n::src::dev::Master* master);

  //Subfunction
  void show_info(k4n::src::dev::Master* master);
  void show_colorization(k4n::src::dev::Master* master);

private:
  k4n::Node* node_kinect;
  k4n::src::dev::Swarm* k4n_swarm;

  int item_width;
};

}
