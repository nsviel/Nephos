#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Master;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::gui{

class Master
{
public:
  //Constructor / Destructor
  Master(eng::k4n::Node* node_k4n);
  ~Master();

  //Main function
  void show_master_info(eng::k4n::dev::Master* master);

  //Subfunction
  void show_info(eng::k4n::dev::Master* master);
  void show_colorization(eng::k4n::dev::Master* master);
  void show_voxelizer(eng::k4n::dev::Master* master);

private:
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
