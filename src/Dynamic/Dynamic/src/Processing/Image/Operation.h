#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace rad{class Node;}
namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread::task{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace dat::atr{class Color;}
namespace dat::atr::normal{class KNN;}


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
  void make_normal_from_depth_image(dyn::base::Sensor* sensor);
  void convert_normal_into_color(dyn::base::Sensor* sensor, std::vector<glm::vec3>& vec_Nxyz);

private:
  dyn::Structure* dyn_struct;
  rad::Node* node_radio;
  utl::thread::task::Pool* thread_pool;

  bool thread_idle = true;
};

}
