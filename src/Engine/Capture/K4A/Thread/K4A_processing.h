#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Utils/Namespace.h>

class Engine;


class K4A_processing
{
public:
  //Constructor / Destructor
  K4A_processing(Engine* engine);
  ~K4A_processing();

public:
  //Main function
  void convert_into_cloud(K4A_device* k4a_device);

  //Loop function
  void loop_init(K4A_device* k4a_device);
  void loop_data(K4A_device* k4a_device);
  void loop_end(K4A_device* k4a_device);

  //Subfunction
  void retrieve_location(int& x, int& y, int& z);
  void retrieve_color(K4A_device* k4a_device, int i);
  void retrieve_ir(K4A_device* k4a_device, int i);
  void retrieve_corner_coordinate(K4A_device* k4a_device);

private:
  Engine* engine;
  eng::kinect::Operation* kin_operation;

  eng::kinect::structure::Cloud* cloud;
  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgba;
  std::vector<float> vec_ir;
};
