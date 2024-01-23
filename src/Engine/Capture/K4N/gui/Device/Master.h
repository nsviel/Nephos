#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


namespace eng::k4n::gui{

class Master
{
public:
  //Constructor / Destructor
  Master(eng::k4n::Node* node_kinect);
  ~Master();

  //Main function
  void show_master_info(eng::k4n::dev::Master* master);

  //Subfunction
  void show_info(eng::k4n::dev::Master* master);
  void show_colorization(eng::k4n::dev::Master* master);

private:
  eng::k4n::Node* node_kinect;
  eng::k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
