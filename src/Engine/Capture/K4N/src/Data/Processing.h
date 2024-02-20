#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace eng::ope{class Voxelizer;}


namespace k4n::thread{

class Processing
{
public:
  //Constructor / Destructor
  Processing(k4n::Node* node_k4n);
  ~Processing();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);

  //Subfunction
  void voxelize_object(k4n::dev::Sensor* sensor);
  void update_object(k4n::dev::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  eng::ope::Voxelizer* ope_voxelizer;

  std::thread thread;
};

}
