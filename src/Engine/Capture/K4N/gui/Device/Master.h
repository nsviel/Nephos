#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

namespace gui{class Node;}


namespace eng::k4n::gui{

class Master
{
public:
  //Constructor / Destructor
  Master(eng::k4n::Node* k4a_node);
  ~Master();

  //Main function
  void show_master_info(eng::k4n::dev::Master* master);

  //Subfunction
  void show_info(eng::k4n::dev::Master* master);
  void show_colorization(eng::k4n::dev::Master* master);
  void show_voxelizer(eng::k4n::dev::Master* master);

private:
  eng::k4n::Node* k4a_node;
  eng::k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
