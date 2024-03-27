#pragma once

#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>

namespace prf::graph{class Tasker;}
namespace k4n{class Node;}
namespace k4n::processing{class Operation;}
namespace k4n::processing{class Calibration;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Operation;}
namespace k4n::structure{class K4N;}
namespace k4n::thread{class Pool;}


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

  //Cloud function
  void convert_into_cloud(k4n::dev::Sensor* sensor);
  void loop_init(k4n::dev::Sensor* sensor);
  void loop_data(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker);
  void loop_end(k4n::dev::Sensor* sensor, prf::graph::Tasker* tasker);

  //Data retrieval
  void retrieve_cloud(k4n::dev::Sensor* sensor, k4a::image& cloud_image);
  void retrieve_location(int i, const int16_t* data);
  void retrieve_color(int i, const uint8_t* rgb_data);
  void retrieve_ir(int i, const uint8_t* ir_data);
  void retrieve_goodness(int i);
  void insert_data(int i);

private:
  k4n::utils::Operation* k4n_operation;
  k4n::processing::Operation* k4n_processing;
  k4n::processing::Calibration* k4n_calibration;
  k4n::thread::Pool* k4n_pool;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgb;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
  std::vector<bool> vec_goodness;

  int16_t* point_cloud_data;
  int point_cloud_size;
  glm::vec3 xyz;
  glm::vec4 rgb;
  float ir;
  float R;
  bool goodness = true;
  bool idle = true;
};

}
