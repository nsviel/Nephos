#include "Cloud.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>


namespace rlx::processing{

//Constructor / Destructor
Cloud::Cloud(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  //---------------------------

  // Generate the pointcloud and texture mappings
  rs2::depth_frame depth = rlx_sensor->device.frame_set.get_depth_frame();
  rs2::pointcloud cloud;
  rs2::points points = cloud.calculate(depth);

  // Tell pointcloud object to map to this color frame
  rs2::video_frame color = rlx_sensor->device.frame_set.get_color_frame();
  buffer.width = color.as<rs2::video_frame>().get_width();
  buffer.height = color.as<rs2::video_frame>().get_height();
  cloud.map_to(color);

  // Get the point cloud data
  const rs2::vertex* vertices = points.get_vertices(); // Array of vertices

  std::vector<glm::vec3> vec_xyz;
  for(int i=0; i<points.size(); i++){
    buffer.xyz.push_back(glm::vec3(vertices[i].x, vertices[i].y, vertices[i].z));
  }



  //---------------------------
}

//Subfunction
void Cloud::extraction_init(dat::base::Sensor& sensor){
  //---------------------------
/*
  buffer.xyz.resize(sensor.cloud.size);
  buffer.rgb.resize(sensor.cloud.size);
  buffer.rgba.resize(sensor.cloud.size);
  buffer.Is.resize(sensor.cloud.size);
  buffer.R.resize(sensor.cloud.size);
*/
  //---------------------------
}
void Cloud::extraction_transfer(dat::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  //Data
  data.xyz = buffer.xyz;

  //Info
  data.size = buffer.xyz.size();
  data.width = buffer.width;
  data.height = buffer.height;

  //---------------------------
}

}
