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
    this->extraction_rgb(*rlx_sensor, i);
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

  rs2::video_frame color = sensor.device.frame_set.get_color_frame();
  cloud.map_to(color);

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
  float y = vertices[i].x;
  float z = -vertices[i].y;

  buffer.xyz[i] = glm::vec3(x, y, z);

  //---------------------------
}
void Cloud::extraction_rgb(rlx::base::Sensor& sensor, int& i){
  const rs2::vertex* vertices = sensor.device.point_set.get_vertices();
  //---------------------------

  // Retrieve color frame
  rs2::video_frame color_frame = sensor.device.frame_set.get_color_frame();
  const uint8_t* color_data = reinterpret_cast<const uint8_t*>(color_frame.get_data());
  int color_width = color_frame.get_width();
  int color_height = color_frame.get_height();

  // Convert vertex coordinates to pixel coordinates (simplified, may need calibration)
  int u = static_cast<int>((vertices[i].x / vertices[i].z) * color_width + color_width / 2);
  int v = static_cast<int>((vertices[i].y / vertices[i].z) * color_height + color_height / 2);

  // Ensure coordinates are within bounds
  u = std::clamp(u, 0, color_width - 1);
  v = std::clamp(v, 0, color_height - 1);

  // Get color data
  int pixel_index = (v * color_width + u) * 3; // RGB has 3 channels

  glm::vec3 rgb(
    color_data[pixel_index + 0] / 255.0f, // R
    color_data[pixel_index + 1] / 255.0f, // G
    color_data[pixel_index + 2] / 255.0f  // B
  );

  glm::vec4 rgba(
    color_data[pixel_index + 0] / 255.0f, // R
    color_data[pixel_index + 1] / 255.0f, // G
    color_data[pixel_index + 2] / 255.0f, // B
    255.0f
  );

  // Assign to buffer
  buffer.rgb[i] = rgb;
  buffer.rgba[i] = rgba;

  //---------------------------
}
void Cloud::extraction_transfer(rlx::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  //Data
  data.xyz = buffer.xyz;
  data.rgb = buffer.rgb;
  data.rgba = buffer.rgba;

  //Info
  data.size = buffer.xyz.size();
  data.width = buffer.width;
  data.height = buffer.height;

  //---------------------------
}

}
