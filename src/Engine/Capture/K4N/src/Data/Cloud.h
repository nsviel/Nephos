#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Operation;}
namespace eng::ope{class Voxelizer;}


namespace k4n::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(k4n::Node* node_k4n);
  ~Cloud();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void convert_into_cloud(k4n::dev::Sensor* sensor);

  //Loop function
  void loop_init(k4n::dev::Sensor* sensor);
  void loop_data(k4n::dev::Sensor* sensor);
  void loop_end(k4n::dev::Sensor* sensor);

  //Data retrieval
  void retrieve_cloud(k4n::dev::Sensor* sensor, k4a::image& cloud_image);
  void retrieve_location(int i, const int16_t* data);
  void retrieve_color(int i, const uint8_t* rgb_data);
  void retrieve_ir(int i, const uint8_t* ir_data);
  void retrieve_goodness(int i);
  void insert_data(int i);

  inline eng::ope::Voxelizer* get_voxelizer(){return ope_voxelizer;}

private:
  k4n::utils::Operation* k4n_operation;
  eng::ope::Voxelizer* ope_voxelizer;

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
