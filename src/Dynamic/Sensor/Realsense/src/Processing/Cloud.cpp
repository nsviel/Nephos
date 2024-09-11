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
  cloud.map_to(color);

  // Get the point cloud data
  const rs2::vertex* vertices = points.get_vertices(); // Array of vertices

  std::vector<glm::vec3> vec_xyz;
  for(int i=0; i<points.size(); i++){
    vec_xyz.push_back(glm::vec3(vertices[i].x, vertices[i].y, vertices[i].z));
  }


  utl::base::Data& data = *sensor.data;
say(vec_xyz.size());
  //Data
  data.xyz = vec_xyz;

  //Info
  data.size = vec_xyz.size();
  data.width = color.as<rs2::video_frame>().get_width();
  data.height = color.as<rs2::video_frame>().get_height();

  //---------------------------
}

}
