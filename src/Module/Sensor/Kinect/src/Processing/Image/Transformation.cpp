#include "Transformation.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Transformation::Transformation(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::make_transformation(k4n::structure::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->config.depth.transformation_mode){
    case k4n::depth::DEPTH_TO_COLOR:{
      this->find_depth_to_color(sensor);
      sensor->cloud.calibration_type = K4A_CALIBRATION_TYPE_COLOR;
      break;
    }
    case k4n::depth::COLOR_TO_DEPTH:{
      this->find_color_to_depth(sensor);
      sensor->cloud.calibration_type = K4A_CALIBRATION_TYPE_DEPTH;
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Transformation::find_depth_to_color(k4n::structure::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Depth images
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->device.calibration.color_camera_calibration.resolution_width,
    sensor->device.calibration.color_camera_calibration.resolution_height,
    sensor->device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  //IR images
  k4a::image ir = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor->ir.data.width,
    sensor->ir.data.height,
    sensor->ir.data.width * static_cast<int>(sizeof(uint16_t)),
    sensor->ir.data.buffer,
    sensor->ir.data.size,
    nullptr,
    nullptr);
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor->device.calibration.color_camera_calibration.resolution_width,
    sensor->device.calibration.color_camera_calibration.resolution_height,
    sensor->device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  uint32_t value_no_data = 0;
  sensor->device.transformation.depth_image_to_color_camera_custom(sensor->depth.data.k4a_image, ir, &depth_transformed, &ir_transformed, K4A_TRANSFORMATION_INTERPOLATION_TYPE_LINEAR, value_no_data);
  if(!depth_transformed.is_valid()) return;

  //Depth transformed
  sensor->depth.data.k4a_image = depth_transformed;
  sensor->depth.data.size = depth_transformed.get_size();
  sensor->depth.data.width = depth_transformed.get_width_pixels();
  sensor->depth.data.height = depth_transformed.get_height_pixels();
  sensor->depth.data.buffer = depth_transformed.get_buffer();

  //IR transformed
  sensor->ir.data.k4a_image = ir_transformed;
  sensor->ir.data.size = ir_transformed.get_size();
  sensor->ir.data.width = ir_transformed.get_width_pixels();
  sensor->ir.data.height = ir_transformed.get_height_pixels();
  sensor->ir.data.buffer = ir_transformed.get_buffer();

  //---------------------------
}
void Transformation::find_color_to_depth(k4n::structure::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_to_depth = sensor->device.transformation.color_image_to_depth_camera(sensor->depth.data.k4a_image, sensor->color.data.k4a_image);
  if(!color_to_depth.is_valid()) return;

  //Fill data structure
  sensor->color.data.k4a_image = color_to_depth;
  sensor->color.data.size = color_to_depth.get_size();
  sensor->color.data.width = color_to_depth.get_width_pixels();
  sensor->color.data.height = color_to_depth.get_height_pixels();
  sensor->color.data.buffer = color_to_depth.get_buffer();

  //---------------------------
}

}
