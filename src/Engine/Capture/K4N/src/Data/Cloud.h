#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/src/Utils/Namespace.h>

class Engine;


namespace k4n::src::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(Engine* engine);
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(k4n::src::dev::Sensor* k4n_sensor);

  //Loop function
  void loop_init(k4n::src::dev::Sensor* k4n_sensor);
  void loop_data(k4n::src::dev::Sensor* k4n_sensor);
  void loop_end(k4n::src::dev::Sensor* k4n_sensor);

  //Subfunction
  void retrieve_location(int& x, int& y, int& z);
  void retrieve_color(k4n::src::dev::Sensor* k4n_sensor, int i);
  void retrieve_ir(k4n::src::dev::Sensor* k4n_sensor, int i);
  void retrieve_corner_coordinate(k4n::src::dev::Sensor* k4n_sensor);

private:
  Engine* engine;
  k4n::src::utils::Operation* kin_operation;

  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgba;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
};

}
