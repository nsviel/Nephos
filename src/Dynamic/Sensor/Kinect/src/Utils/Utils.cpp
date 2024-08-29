#include "Utils.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n{

//Constructor / Destructor
Utils::Utils(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_set = node_element->get_dat_set();
  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
Utils::~Utils(){}

//Main function
void Utils::insert_in_kinect_set(k4n::base::Sensor& sensor){
  //---------------------------

  //Get kinect set
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(set_graph, "kinect");

  //If it doesn't exists, create it
  if(!set){
    set = std::make_shared<dat::base::Set>();
    set->name = "kinect";
    set->icon = ICON_FA_USER;
    set->is_locked = false;
    set->is_suppressible = true;
    dat_set->add_subset(set_graph, set);
  }

  //Assign to sensor
  sensor.set_parent = set;

  //---------------------------
}
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
