#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace prf{class Tasker;}
namespace k4n{class Node;}
namespace k4n::data{class Processing;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Operation;}


namespace k4n::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud();
  ~Cloud();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);

  //Cloud function
  void convert_into_cloud(k4n::dev::Sensor* sensor);
  void loop_init(k4n::dev::Sensor* sensor);
  void loop_data(k4n::dev::Sensor* sensor, prf::Tasker* tasker);
  void loop_end(k4n::dev::Sensor* sensor, prf::Tasker* tasker);

  //Data retrieval
  void retrieve_cloud(k4n::dev::Sensor* sensor, k4a::image& cloud_image);
  void retrieve_location(int i, const int16_t* data);
  void retrieve_color(int i, const uint8_t* rgb_data);
  void retrieve_ir(int i, const uint8_t* ir_data);
  void retrieve_goodness(int i);
  void insert_data(int i);

private:
  k4n::utils::Operation* k4n_operation;
  k4n::data::Processing* k4n_processing;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgb;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
  std::vector<bool> vec_goodness;

  std::thread thread;
  bool thread_running = false;
  int16_t* point_cloud_data;
  int point_cloud_size;
  glm::vec3 xyz;
  glm::vec4 rgb;
  float ir;
  float R;
  bool goodness = true;
};

}
