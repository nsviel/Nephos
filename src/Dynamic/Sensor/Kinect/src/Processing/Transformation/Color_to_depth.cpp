#include "Color_to_depth.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Core/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Color_to_depth::Color_to_depth(k4n::Node* node_k4n){
  //---------------------------

  this->table_xy = new k4n::processing::image::Table_xy(node_k4n);

  //---------------------------
}
Color_to_depth::~Color_to_depth(){}

//Main function
void Color_to_depth::make_transformation(k4n::base::Sensor* sensor){
  //---------------------------

  this->k4a_color_to_depth(sensor);
  sensor->cloud.calibration_type = K4A_CALIBRATION_TYPE_DEPTH;

  //---------------------------
}

//Subfunction
void Color_to_depth::k4a_color_to_depth(k4n::base::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_to_depth = k4a::image::create(
    K4A_IMAGE_FORMAT_COLOR_BGRA32,
    sensor->depth.data.width,
    sensor->depth.data.height,
    sensor->depth.data.width * 4
  );
  sensor->device.transformation.color_image_to_depth_camera(sensor->depth.data.k4a_image, sensor->color.data.k4a_image, &color_to_depth);
  if(!color_to_depth.is_valid()) return;

  //Fill data structure
  sensor->color.data.k4a_image = color_to_depth;
  sensor->color.data.size = color_to_depth.get_size();
  sensor->color.data.width = color_to_depth.get_width_pixels();
  sensor->color.data.height = color_to_depth.get_height_pixels();
  sensor->color.data.buffer = color_to_depth.get_buffer();

  //---------------------------
}
void Color_to_depth::table_color_to_depth(k4n::base::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------


  //---------------------------
}

}
