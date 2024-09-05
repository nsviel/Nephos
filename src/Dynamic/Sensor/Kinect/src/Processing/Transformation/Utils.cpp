#include "Utils.h"

#include <Kinect/Namespace.h>


namespace k4n{

//Constructor / Destructor
Utils::Utils(k4n::Node* node_k4n){
  //---------------------------


  //---------------------------
}
Utils::~Utils(){}

//Main function
glm::vec3 Utils::convert_depth_2d_to_3d(k4n::base::Sensor& sensor, glm::ivec2 point_2d){
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor.depth.data.buffer);
  int width = sensor.depth.data.width;

  //Retrieve image coordinates
  int x = point_2d[0];
  int y = point_2d[1];
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float3_t target_xyz;
  bool success = sensor.device.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  glm::vec4 xyzw = glm::vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

  //Apply transformation
  float inv_scale = 1.0f / 1000.0f;
  xyzw.x = -xyzw.x * inv_scale;
  xyzw.y = -xyzw.y * inv_scale;
  xyzw.z = xyzw.z * inv_scale;
  glm::vec3 pose = glm::vec3(xyzw.z, xyzw.x, xyzw.y);

  //---------------------------
  return pose;
}

}
