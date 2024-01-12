#pragma once

#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>

class Engine;


namespace k4n::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(Engine* engine);
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(k4n::device::Device* k4a_device);

  //Loop function
  void loop_init(k4n::device::Device* k4a_device);
  void loop_data(k4n::device::Device* k4a_device);
  void loop_end(k4n::device::Device* k4a_device);

  //Subfunction
  void retrieve_location(int& x, int& y, int& z);
  void retrieve_color(k4n::device::Device* k4a_device, int i);
  void retrieve_ir(k4n::device::Device* k4a_device, int i);
  void retrieve_corner_coordinate(k4n::device::Device* k4a_device);

private:
  Engine* engine;
  k4n::utils::Operation* kin_operation;

  k4n::structure::Cloud* cloud;
  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgba;
  std::vector<float> vec_ir;
  std::vector<float> vec_r;
};

}
