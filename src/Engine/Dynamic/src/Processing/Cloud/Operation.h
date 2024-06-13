#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Entity;}
namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Recorder;}
namespace dyn::base{class Sensor;}
namespace dat::base{class Entity;}
namespace utl::thread{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace dyn::cloud{class Normal;}


namespace dyn::cloud{

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
  void colorize_object(dat::base::Entity* entity);
  void voxelize_object(dyn::base::Sensor* sensor);
  void triangularize_object(dyn::base::Sensor* sensor);
  void update_object(dyn::base::Sensor* sensor);

private:
  dat::Entity* dat_entity;
  dyn::Structure* dyn_struct;
  dyn::cloud::Recorder* dyn_recorder;
  ope::Voxelizer* ope_voxelizer;
  ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;
  dyn::cloud::Normal* dyn_normal;

  utl::thread::Pool* thread_pool;
  bool thread_idle = true;
};

}
