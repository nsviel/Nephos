#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace ope::normal{class KNN;}
namespace rad::detection::cloud{class Detection;}


namespace dyn::cloud{

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
  dyn::Structure* dyn_struct;
  ope::Voxelizer* ope_voxelizer;
  ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;
  ope::normal::KNN* ope_normal;
  rad::detection::cloud::Detection* rad_detection;

  utl::thread::Pool* thread_pool;

  bool thread_idle = true;
};

}