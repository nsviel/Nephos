#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::utils{class Operation;}
namespace eng::ope{class Voxelizer;}


namespace eng::k4n::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(eng::k4n::Node* node_k4n);
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(eng::k4n::dev::Sensor* sensor);

  //Loop function
  void loop_init(eng::k4n::dev::Sensor* sensor);
  void loop_data(eng::k4n::dev::Sensor* sensor);
  void loop_end(eng::k4n::dev::Sensor* sensor);

  //Data retrieval
  void retrieve_cloud(eng::k4n::dev::Sensor* sensor, k4a::image& cloud_image);
  void retrieve_location(eng::k4n::dev::Sensor* sensor, int i, int16_t* data);
  void retrieve_color(eng::k4n::dev::Sensor* sensor, int i);
  void retrieve_ir(eng::k4n::dev::Sensor* sensor, int i);
  void retrieve_goodness(int i);
  void insert_data();

  inline eng::ope::Voxelizer* get_voxelizer(){return ope_voxelizer;}

private:
  eng::Node* engine;
  eng::k4n::utils::Operation* k4n_operation;
  eng::ope::Voxelizer* ope_voxelizer;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgb;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
  std::vector<bool> vec_goodness;

  glm::vec3 xyz;
  glm::vec4 rgb;
  float ir;
  float R;
  bool goodness;
};

}
