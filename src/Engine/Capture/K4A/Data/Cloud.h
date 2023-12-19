#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Utility/Specific/common.h>

class Engine;


namespace eng::kinect::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(Engine* engine);
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(K4A_device* k4a_device);

  //Subfunction
  void retrieve_location(K4A_device* k4a_device);
  void retrieve_color(K4A_device* k4a_device, int i);
  void retrieve_corner_coordinate(K4A_device* k4a_device);

private:
  Engine* engine;

  eng::kinect::structure::Cloud* cloud;
  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec4> vec_rgba;
};

}
