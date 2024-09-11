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

  this->extraction_init(*rlx_sensor);

  for(int i=0; i<rlx_sensor->device.point_set.size(); i++){
    this->extraction_xyz(*rlx_sensor, i);
  }

  this->extraction_transfer(*rlx_sensor);

/*
  // Tell pointcloud object to map to this color frame
  rs2::video_frame color = rlx_sensor->device.frame_set.get_color_frame();
  buffer.width = color.as<rs2::video_frame>().get_width();
  buffer.height = color.as<rs2::video_frame>().get_height();
  cloud.map_to(color);
*/


  //---------------------------
}

//Subfunction
void Cloud::extraction_init(rlx::base::Sensor& sensor){
  //---------------------------

  // Generate the pointcloud and texture mappings
  rs2::depth_frame depth = sensor.device.frame_set.get_depth_frame();
  rs2::pointcloud cloud;
  sensor.device.point_set = cloud.calculate(depth);
  int size = sensor.device.point_set.size();

  //Resize buffer
  buffer.xyz.resize(size);
  buffer.rgb.resize(size);
  buffer.rgba.resize(size);
  buffer.uv.resize(size);
  buffer.R.resize(size);

  //---------------------------
}
void Cloud::extraction_xyz(rlx::base::Sensor& sensor, int& i){
  const rs2::vertex* vertices = sensor.device.point_set.get_vertices();
  //---------------------------

  //Convert X axis oriented.
  float x = vertices[i].z;
  float y = -vertices[i].y;
  float z = vertices[i].x;

  buffer.xyz[i] = glm::vec3(x, y, z);

  //---------------------------
}
void Cloud::extraction_transfer(rlx::base::Sensor& sensor){
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
