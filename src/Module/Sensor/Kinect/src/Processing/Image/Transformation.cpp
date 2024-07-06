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

  this->tj_handle = tjInitDecompress();
  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Transformation::~Transformation(){
  //---------------------------

  tjDestroy(tj_handle);

  //---------------------------
}

//Main function
void Transformation::find_depth_to_color(k4n::structure::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->device.calibration.color_camera_calibration.resolution_width,
    sensor->device.calibration.color_camera_calibration.resolution_height,
    sensor->device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  sensor->device.transformation.depth_image_to_color_camera(sensor->depth.data.k4a_image, &depth_transformed);
  if(!depth_transformed.is_valid()) return;

  //Data
  sensor->depth.cloud.name = "depth_to_color";
  sensor->depth.cloud.k4a_image = depth_transformed;
  sensor->depth.cloud.size = depth_transformed.get_size();
  sensor->depth.cloud.width = depth_transformed.get_width_pixels();
  sensor->depth.cloud.height = depth_transformed.get_height_pixels();
  sensor->depth.cloud.buffer = depth_transformed.get_buffer();
  sensor->depth.cloud.format = sensor->depth.data.format;

  //---------------------------
}
void Transformation::find_depth_and_ir_to_color(k4n::structure::Sensor* sensor){
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
  sensor->depth.cloud.name = "depth_to_color";
  sensor->depth.cloud.k4a_image = depth_transformed;
  sensor->depth.cloud.size = depth_transformed.get_size();
  sensor->depth.cloud.width = depth_transformed.get_width_pixels();
  sensor->depth.cloud.height = depth_transformed.get_height_pixels();
  sensor->depth.cloud.buffer = depth_transformed.get_buffer();
  sensor->depth.cloud.format = sensor->depth.data.format;

  //IR transformed
  sensor->ir.cloud.name = "ir_to_color";
  sensor->ir.cloud.k4a_image = ir_transformed;
  sensor->ir.cloud.size = ir_transformed.get_size();
  sensor->ir.cloud.width = ir_transformed.get_width_pixels();
  sensor->ir.cloud.height = ir_transformed.get_height_pixels();
  sensor->ir.cloud.buffer = ir_transformed.get_buffer();
  sensor->ir.cloud.format = sensor->ir.data.format;

  //---------------------------
}
void Transformation::find_ir_to_color(k4n::structure::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->ir.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->device.calibration.color_camera_calibration.resolution_width,
    sensor->device.calibration.color_camera_calibration.resolution_height,
    sensor->device.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  k4a::image ir = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->ir.data.width,
    sensor->ir.data.height,
    sensor->ir.data.width * static_cast<int>(sizeof(uint16_t)),
    sensor->ir.data.buffer,
    sensor->ir.data.size,
    nullptr,
    nullptr);

  sensor->device.transformation.depth_image_to_color_camera(ir, &ir_transformed);
  if(!ir_transformed.is_valid()) return;

  //Data
  sensor->ir.cloud.name = "depth_to_color";
  sensor->ir.cloud.k4a_image = ir_transformed;
  sensor->ir.cloud.size = ir_transformed.get_size();
  sensor->ir.cloud.width = ir_transformed.get_width_pixels();
  sensor->ir.cloud.height = ir_transformed.get_height_pixels();
  sensor->ir.cloud.buffer = ir_transformed.get_buffer();
  sensor->ir.cloud.format = sensor->ir.data.format;

  //---------------------------
}
void Transformation::find_color_to_depth(k4n::structure::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  if(sensor->color.data.format == "YUY2"){
    sensor->color.data.k4a_image = k4a::image::create_from_buffer(
      K4A_IMAGE_FORMAT_COLOR_BGRA32,
      sensor->ir.data.width,
      sensor->ir.data.height,
      sensor->ir.data.width * static_cast<int>(sizeof(uint32_t)),
      retrieve_bgra_from_yuy2(sensor->color.data.buffer, sensor->ir.data.width, sensor->ir.data.height),
      sensor->ir.data.width * sensor->ir.data.height * 3,
      nullptr,
      nullptr);
    sensor->color.data.format = "B8G8R8A8_SRGB";
  }

  //Convert it into a depth POV representation
  k4a::image color_to_depth = sensor->device.transformation.color_image_to_depth_camera(sensor->depth.data.k4a_image, sensor->color.data.k4a_image);
  if(!color_to_depth.is_valid()) return;

  //Fill data structure
  sensor->color.cloud.name = "color_to_depth";
  sensor->color.cloud.k4a_image = color_to_depth;
  sensor->color.cloud.size = color_to_depth.get_size();
  sensor->color.cloud.width = color_to_depth.get_width_pixels();
  sensor->color.cloud.height = color_to_depth.get_height_pixels();
  sensor->color.cloud.buffer = color_to_depth.get_buffer();
  sensor->color.cloud.format = sensor->color.data.format;
  sensor->color.cloud.timestamp = sensor->color.data.timestamp;

  //---------------------------
  //color_to_depth.reset();
}

//Subfunction
uint8_t* Transformation::retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height){
  uint8_t* bgrImage = new uint8_t[width * height * 3];
  //---------------------------

  for(int i = 0; i < width * height; i += 2){
    uint8_t y0 = yuy2Image[2 * i];
    uint8_t u = yuy2Image[2 * i + 1];
    uint8_t y1 = yuy2Image[2 * i + 2];
    uint8_t v = yuy2Image[2 * i + 3];

    // Convert YUV to RGB
    int c = y0 - 16;
    int d = u - 128;
    int e = v - 128;

    int r0 = (298 * c + 409 * e + 128) >> 8;
    int g0 = (298 * c - 100 * d - 208 * e + 128) >> 8;
    int b0 = (298 * c + 516 * d + 128) >> 8;

    c = y1 - 16;

    int r1 = (298 * c + 409 * e + 128) >> 8;
    int g1 = (298 * c - 100 * d - 208 * e + 128) >> 8;
    int b1 = (298 * c + 516 * d + 128) >> 8;

    // Store BGR values
    bgrImage[3 * i] = static_cast<uint8_t>(std::max(0, std::min(255, b0)));
    bgrImage[3 * i + 1] = static_cast<uint8_t>(std::max(0, std::min(255, g0)));
    bgrImage[3 * i + 2] = static_cast<uint8_t>(std::max(0, std::min(255, r0)));
    bgrImage[3 * i + 3] = static_cast<uint8_t>(std::max(0, std::min(255, b1)));
    bgrImage[3 * i + 4] = static_cast<uint8_t>(std::max(0, std::min(255, g1)));
    bgrImage[3 * i + 5] = static_cast<uint8_t>(std::max(0, std::min(255, r1)));
  }

  //---------------------------
  return bgrImage;
}


}
