#include "Depth_to_color.h"

#include <Kinect/Namespace.h>


namespace k4n::transformation{

//Constructor / Destructor
Depth_to_color::Depth_to_color(k4n::Node* node_k4n){
  //---------------------------


  //---------------------------
}
Depth_to_color::~Depth_to_color(){}

//Main function
void Depth_to_color::make_transformation(k4n::base::Sensor& sensor){
  if(!check_data(sensor)) return;
  //---------------------------

  this->find_depth_to_color(sensor);
  sensor.cloud.calibration_type = K4A_CALIBRATION_TYPE_COLOR;

  //---------------------------
}

//Subfunction
void Depth_to_color::find_depth_to_color(k4n::base::Sensor& sensor){
  //---------------------------

  //Depth images
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor.device.calibration.color_camera_calibration.resolution_width,
    sensor.device.calibration.color_camera_calibration.resolution_height,
    sensor.device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t))
  );

  //IR images
  k4a::image ir = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor.infra.data.width,
    sensor.infra.data.height,
    sensor.infra.data.width * static_cast<int>(sizeof(uint16_t)),
    sensor.infra.data.buffer,
    sensor.infra.data.size,
    nullptr,
    nullptr
  );
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM16,
    sensor.device.calibration.color_camera_calibration.resolution_width,
    sensor.device.calibration.color_camera_calibration.resolution_height,
    sensor.device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t))
  );

  uint32_t value_no_data = 0;
  sensor.device.transformation.depth_image_to_color_camera_custom(sensor.depth.data.image, ir, &depth_transformed, &ir_transformed, K4A_TRANSFORMATION_INTERPOLATION_TYPE_LINEAR, value_no_data);
  if(!depth_transformed.is_valid()) return;

  //Depth transformed
  sensor.depth.data.image = depth_transformed;
  sensor.depth.data.size = depth_transformed.get_size();
  sensor.depth.data.width = depth_transformed.get_width_pixels();
  sensor.depth.data.height = depth_transformed.get_height_pixels();
  sensor.depth.data.buffer = depth_transformed.get_buffer();

  //IR transformed
  sensor.infra.data.image = ir_transformed;
  sensor.infra.data.size = ir_transformed.get_size();
  sensor.infra.data.width = ir_transformed.get_width_pixels();
  sensor.infra.data.height = ir_transformed.get_height_pixels();
  sensor.infra.data.buffer = ir_transformed.get_buffer();

  //---------------------------
}
bool Depth_to_color::check_data(k4n::base::Sensor& sensor){
  //---------------------------

  if(!sensor.color.data.image || !sensor.depth.data.image) return false;
  if(sensor.depth.data.image.get_format() != K4A_IMAGE_FORMAT_DEPTH16) return false;
  if(sensor.color.data.image.get_format() != K4A_IMAGE_FORMAT_COLOR_BGRA32) return false;
  if(sensor.depth.data.width == sensor.color.data.width) return false;

  //---------------------------
  return true;
}

}
