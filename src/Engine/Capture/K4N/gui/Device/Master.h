#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Master
{
public:
  //Constructor / Destructor
  Master(k4n::Node* node_k4n);
  ~Master();

  //Main function
  void show_master_info(k4n::dev::Master* master);

  //Subfunction
  void show_info(k4n::dev::Master* master);
  void show_colorization(k4n::dev::Master* master);
  void show_voxelizer(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
