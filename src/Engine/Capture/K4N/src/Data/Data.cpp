#include "Data.h"

#include <K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Data::Data(){
  //---------------------------

  this->tj_handle = tjInitDecompress();
  this->k4a_depth = new k4n::data::Depth();
  this->k4a_infrared = new k4n::data::Infrared();

  //---------------------------
}
Data::~Data(){
  //---------------------------

  tjDestroy(tj_handle);

  //---------------------------
}

//Main function
void Data::find_data_from_capture(k4n::dev::Sensor* sensor, k4a::capture capture){
  prf::Tasker* tasker = sensor->profiler->get_tasker("data");
  //---------------------------

  //Capture data
  tasker->task_begin("data::base");
  this->find_data_depth(sensor, capture);
  this->find_data_color(sensor, capture);
  this->find_data_ir(sensor, capture);
  tasker->task_end("data::base");

  //Cloud data
  tasker->task_begin("data::transformation");
  this->find_data_cloud(sensor, capture);
  tasker->task_end("data::transformation");

  //Finish
  sensor->master->player.ts_cur = sensor->color.data.timestamp;
  sensor->param.data_ready = true;

  //---------------------------
}

//Data function
void Data::find_data_depth(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------

  //Get k4a image
  k4a::image depth = capture.get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor->depth.data.name = "depth";
  sensor->depth.data.k4a_image = depth;
  sensor->depth.data.width = depth.get_width_pixels();
  sensor->depth.data.height = depth.get_height_pixels();
  sensor->depth.data.buffer = depth.get_buffer();
  sensor->depth.data.size = depth.get_size();
  sensor->depth.data.format = retrieve_format_from_k4a(depth.get_format());
  sensor->depth.data.temperature = capture.get_temperature_c();
  sensor->depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
  depth.reset();
}
void Data::find_data_color(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------

  //Get k4a image
  k4a::image color = capture.get_color_image();
  if(!color.is_valid()) return;

  //Data
  sensor->color.data.name = "color";
  sensor->color.data.k4a_image = color;
  sensor->color.data.size = color.get_size();
  sensor->color.data.width = color.get_width_pixels();
  sensor->color.data.height = color.get_height_pixels();
  sensor->color.data.buffer = color.get_buffer();
  sensor->color.data.format = retrieve_format_from_k4a(color.get_format());
  sensor->color.data.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
  color.reset();
}
void Data::find_data_ir(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------

  //Get k4a image
  k4a::image ir = capture.get_ir_image();
  if(!ir.is_valid()) return;

  //Data
  sensor->ir.data.name = "ir";
  sensor->ir.data.k4a_image = ir;
  sensor->ir.data.width = ir.get_width_pixels();
  sensor->ir.data.height = ir.get_height_pixels();
  sensor->ir.data.buffer = ir.get_buffer();
  sensor->ir.data.buffer = ir.get_buffer();
  sensor->ir.data.size = ir.get_size();
  sensor->ir.data.format = retrieve_format_from_k4a(ir.get_format());
  sensor->ir.data.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);

  //---------------------------
  ir.reset();
}

//Transformed data
void Data::find_data_cloud(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------

  switch(sensor->master->operation.transformation_mode){
    case k4n::transformation::DEPTH_TO_COLOR:{
      this->find_depth_and_ir_to_color(sensor, capture, sensor->param.transformation);
      sensor->color.cloud = sensor->color.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_COLOR;
      break;
    }
    case k4n::transformation::COLOR_TO_DEPTH:{
      this->find_color_to_depth(sensor, capture, sensor->param.transformation);
      sensor->depth.cloud = sensor->depth.data;
      sensor->ir.cloud = sensor->ir.data;
      sensor->depth.cloud.calibration_type = K4A_CALIBRATION_TYPE_DEPTH;
      break;
    }
  }

  //---------------------------
}
void Data::find_depth_to_color(k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  transformation.depth_image_to_color_camera(sensor->depth.data.k4a_image, &depth_transformed);
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
void Data::find_depth_and_ir_to_color(k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Depth images
  k4a::image depth_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
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
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  uint32_t value_no_data = 0;
  transformation.depth_image_to_color_camera_custom(sensor->depth.data.k4a_image, ir, &depth_transformed, &ir_transformed, K4A_TRANSFORMATION_INTERPOLATION_TYPE_LINEAR, value_no_data);
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
void Data::find_ir_to_color(k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.k4a_image || !sensor->ir.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image ir_transformed = k4a::image::create(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
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

  transformation.depth_image_to_color_camera(ir, &ir_transformed);
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
void Data::find_color_to_depth(k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_from_depth = transformation.color_image_to_depth_camera(sensor->depth.data.k4a_image, sensor->color.data.k4a_image);
  if(!color_from_depth.is_valid()) return;

  //Fill data structure
  sensor->color.cloud.name = "color_to_depth";
  sensor->color.cloud.k4a_image = color_from_depth;
  sensor->color.cloud.size = color_from_depth.get_size();
  sensor->color.cloud.width = color_from_depth.get_width_pixels();
  sensor->color.cloud.height = color_from_depth.get_height_pixels();
  sensor->color.cloud.buffer = color_from_depth.get_buffer();
  sensor->color.cloud.format = sensor->color.data.format;
  sensor->color.cloud.timestamp = sensor->color.data.timestamp;

  //---------------------------
  //color_from_depth.reset();
}

//Subfunction
string Data::retrieve_format_from_k4a(k4a_image_format_t color_format){
  string format = "";
  //---------------------------

  if(color_format == K4A_IMAGE_FORMAT_COLOR_MJPG){
    format = "MJPEG";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_NV12){
    format = "NV12";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_YUY2){
    format = "YUY2";
  }else if(color_format == K4A_IMAGE_FORMAT_COLOR_BGRA32){
    format = "B8G8R8A8_SRGB";
  }else if(color_format == K4A_IMAGE_FORMAT_DEPTH16){
    format = "DEPTH16";
  }else if(color_format == K4A_IMAGE_FORMAT_IR16){
    format = "IR16";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM8){
    format = "CUSTOM8";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM16){
    format = "CUSTOM16";
  }else if(color_format == K4A_IMAGE_FORMAT_CUSTOM){
    format = "CUSTOM";
  }

  //---------------------------
  return format;
}
void Data::retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format){
  //---------------------------

  if(format == "MJPEG"){
    this->retrieve_bgra_from_mjpeg(image, data);
    format = "B8G8R8A8_SRGB";
  }else{
    uint8_t* image_data = image.get_buffer();
    size_t size = image.get_size();
    data = std::vector<uint8_t>(image_data, image_data + size);
    format = "B8G8R8A8_SRGB";
  }

  //---------------------------
}
void Data::retrieve_bgra_from_mjpeg(k4a::image& image, vector<uint8_t>& data){
  //---------------------------

  int width = image.get_width_pixels();
  int height = image.get_height_pixels();
  int size = image.get_size();
  uint8_t* mpeg = image.get_buffer();
  vector<uint8_t> bgra(width * height * tjPixelSize[TJPF_RGBA]);
  int flags = TJFLAG_FASTDCT | TJFLAG_FASTUPSAMPLE;

  int ret = tjDecompress2(tj_handle, &mpeg[0], size, bgra.data(), width, 0, height, TJPF_RGBA, flags);
  if(ret != 0){
    cout<<"[error] MPEG convertion error"<<endl;
  }
  data = bgra;

  //Creat a new k4a image with RGBA data format
  image = k4a::image::create_from_buffer(K4A_IMAGE_FORMAT_COLOR_BGRA32, width, height, width * 4, data.data(), data.size(), nullptr, nullptr);

  //---------------------------
}


}
