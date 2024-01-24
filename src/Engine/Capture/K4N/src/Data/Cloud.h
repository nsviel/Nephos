#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>

class Engine;


namespace eng::k4n::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(Engine* engine);
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(eng::k4n::dev::Sensor* k4n_sensor);

  //Loop function
  void loop_init(eng::k4n::dev::Sensor* k4n_sensor);
  void loop_data(eng::k4n::dev::Sensor* k4n_sensor);
  void loop_end(eng::k4n::dev::Sensor* k4n_sensor);

  //Subfunction
  void retrieve_location(eng::k4n::dev::Sensor* k4n_sensor, int i, int16_t* data);
  void retrieve_color(eng::k4n::dev::Sensor* k4n_sensor, int i);
  void retrieve_ir(eng::k4n::dev::Sensor* k4n_sensor, int i);
  void retrieve_corner_coordinate(eng::k4n::dev::Sensor* k4n_sensor);

  inline eng::ope::Voxelizer* get_voxelizer(){return ope_voxelizer;}

private:
  Engine* engine;
  eng::k4n::utils::Operation* k4n_operation;
  eng::ope::Voxelizer* ope_voxelizer;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgba;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
  std::vector<bool> vec_idx;
};

}
