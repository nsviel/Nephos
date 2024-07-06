#pragma once

#include <glm/glm.hpp>
#include <k4a/k4a.hpp>
#include <vector>

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace prf::dynamic{class Tasker;}
namespace utl::thread{class Pool;}
namespace dyn::cloud{class Operation;}
namespace k4n::processing{class Operation;}


namespace k4n::processing{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(k4n::Node* node_k4n);
  ~Cloud();

public:
  //Main function
  void start_thread(k4n::structure::Sensor* sensor);
  void run_thread(k4n::structure::Sensor* sensor);
  void wait_thread();

  //Loop function
  void convert_image_into_cloud(k4n::structure::Sensor* sensor);
  void convertion_init(k4n::structure::Sensor* sensor);
  void convertion_data(k4n::structure::Sensor* sensor);
  void convertion_transfer(k4n::structure::Sensor* sensor);

  //Data retrieval
  void retrieve_table_xy(k4n::structure::Sensor* sensor);
  void retrieve_cloud(k4n::structure::Sensor* sensor);
  void retrieve_location(k4n::structure::Sensor* sensor, int i);
  void retrieve_color(k4n::structure::Sensor* sensor, int i);
  void retrieve_ir(k4n::structure::Sensor* sensor, int i);
  void insert_data(int i);

private:
  utl::thread::Pool* thread_pool;
  dyn::cloud::Operation* dyn_operation;
  k4n::processing::Operation* k4n_operation;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec3> vec_rgb;
  std::vector<glm::vec4> vec_rgba;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;

  glm::vec3 xyz;
  glm::vec3 rgb;
  float ir;
  float R;
  bool thread_idle = true;
};

}
