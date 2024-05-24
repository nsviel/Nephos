#pragma once

#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace prf::graph{class Tasker;}
namespace utl::thread{class Pool;}
namespace dyn::cloud{class Operation;}



namespace k4n::processing{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(k4n::Node* node_k4n);
  ~Cloud();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Loop function
  void convertion_into_cloud(k4n::dev::Sensor* sensor);
  void convertion_init(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker);
  void convertion_data(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker);
  void convertion_transfer(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker);

  //Data retrieval
  void retrieve_cloud(k4n::dev::Sensor* sensor);
  void retrieve_location(k4n::dev::Sensor* sensor, int i);
  void retrieve_color(k4n::dev::Sensor* sensor, int i);
  void retrieve_ir(k4n::dev::Sensor* sensor, int i);
  void insert_data(int i);

private:
  utl::thread::Pool* thread_pool;
  dyn::cloud::Operation* dyn_operation;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgb;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;

  glm::vec3 xyz;
  glm::vec4 rgb;
  float ir;
  float R;
  bool thread_idle = true;
};

}
