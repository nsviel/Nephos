#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace ope::normal{class KNN;}


namespace dyn::image{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction

private:
  dyn::Structure* dyn_struct;
  utl::thread::Pool* thread_pool;

  bool thread_idle = true;
};

}
