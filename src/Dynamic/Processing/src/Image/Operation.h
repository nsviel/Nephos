#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace rad{class Node;}
namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::base{class Sensor;}
namespace thr::task{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace dat::atr{class Color;}
namespace dat::atr::normal{class KNN;}


namespace dyn::prc::image{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dyn::prc::Node* node_processing);
  ~Operation();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void make_normal_from_depth_image(std::shared_ptr<dat::base::Sensor> sensor);
  void convert_normal_into_color(std::shared_ptr<dat::base::Sensor> sensor, std::vector<glm::vec3>& vec_Nxyz);

private:
  dyn::prc::Structure* dyn_struct;
  rad::Node* node_radio;
  thr::task::Pool* thread_pool;

  bool thread_idle = true;
};

}
