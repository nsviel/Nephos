#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace ope::normal{class KNN;}


namespace dyn::processing{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::Node* node_dynamic);
  ~Operation();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void colorize_object(dat::base::Sensor* sensor);
  void voxelize_object(dat::base::Sensor* sensor);
  void triangularize_object(dat::base::Sensor* sensor);
  void update_object(dat::base::Sensor* sensor);

private:
  ope::Voxelizer* ope_voxelizer;
  ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;
  ope::normal::KNN* ope_normal;

  utl::thread::Pool* thread_pool;

  bool idle = true;
};

}
