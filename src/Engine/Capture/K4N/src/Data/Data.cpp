#include "Data.h"

#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n::data{

//Constructor / Destructor
Data::Data(){
  //---------------------------

  this->tj_handle = tjInitDecompress();

  //---------------------------
}
Data::~Data(){
  //---------------------------

  tjDestroy(tj_handle);

  //---------------------------
}

//Main function
void Data::find_data_from_capture(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------

  //Capture data
  this->find_depth(sensor, capture);
  this->find_color(sensor, capture);
  this->find_ir(sensor, capture);

  //Transformed data
  this->find_color_to_depth(sensor, capture, sensor->param.transformation);
  this->find_depth_to_color(sensor, capture, sensor->param.transformation);

  //Finish
  sensor->master->player.ts_cur = sensor->color.data.timestamp;
  sensor->param.data_ready = true;

  //---------------------------
}

//Data function
void Data::find_depth(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  k4a::image depth = capture.get_depth_image();
  //---------------------------

  //Get specific information
  if(!depth || !depth.is_valid()){
    cout<<"[error] kinect depth image invalid"<<endl;
    return;
  }
  float timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(depth.get_format());

  //Buffer
  this->retrieve_data_from_capture(depth, sensor->depth.data.buffer, format);
  sensor->depth.data.size = sensor->depth.data.buffer.size();

  //Data
  sensor->depth.data.image = depth;
  sensor->depth.data.name = "depth";
  sensor->depth.data.width = depth.get_width_pixels();
  sensor->depth.data.height = depth.get_height_pixels();
  sensor->depth.data.format = format;
  sensor->depth.data.temperature = capture.get_temperature_c();
  sensor->depth.data.timestamp = timestamp;

  //---------------------------
  depth.reset();
}
void Data::find_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  k4a::image color = capture.get_color_image();
  //---------------------------

  //Get specific information
  if(!color || !color.is_valid()){
    return;
  }
  float timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(color.get_format());
  this->retrieve_data_from_capture(color, sensor->color.data.buffer, format);

  //Fill data structure
  sensor->color.data.image = color;
  sensor->color.data.name = "color";
  sensor->color.data.size = sensor->color.data.buffer.size();
  sensor->color.data.width = color.get_width_pixels();
  sensor->color.data.height = color.get_height_pixels();
  sensor->color.data.format = format;
  sensor->color.data.timestamp = timestamp;

  //---------------------------
  color.reset();
}
void Data::find_ir(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  k4a::image ir = capture.get_ir_image();
  //---------------------------

  //Get specific information
  if(!ir || !ir.is_valid()){
    cout<<"[error] kinect ir image invalid"<<endl;
    return;
  }
  float timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(ir.get_format());
  this->retrieve_data_from_capture(ir, sensor->ir.data.buffer, format);

  //Fill data structure
  sensor->ir.data.image = ir;
  sensor->ir.data.name = "ir";
  sensor->ir.data.size = sensor->ir.data.buffer.size();
  sensor->ir.data.width = ir.get_width_pixels();
  sensor->ir.data.height = ir.get_height_pixels();
  sensor->ir.data.format = format;
  sensor->ir.data.timestamp = timestamp;

  //---------------------------
  ir.reset();
}

//Transformed data
void Data::find_depth_to_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.image || !sensor->depth.data.image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image image_transformed = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
    sensor->param.calibration.color_camera_calibration.resolution_width,
    sensor->param.calibration.color_camera_calibration.resolution_height,
    sensor->param.calibration.color_camera_calibration.resolution_width *
    static_cast<int>(sizeof(uint16_t)));

  transformation.depth_image_to_color_camera(sensor->depth.data.image, &image_transformed);
  if(!image_transformed || !image_transformed.is_valid()){
    return;
  }
/*
  //Buffer
  string format = retrieve_format_from_k4a(depth.get_format());
  this->retrieve_data_from_capture(image_transformed, sensor->depth.data.buffer, sensor->depth.data.format);
  sensor->depth.data.size = sensor->depth.data.buffer.size();

  //Data
  sensor->depth.data.image = image_transformed;
  sensor->depth.data.width = image_transformed.get_width_pixels();
  sensor->depth.data.height = image_transformed.get_height_pixels();
*/
  //---------------------------
}
void Data::find_color_to_depth(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.data.image || !sensor->depth.data.image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_from_depth = transformation.color_image_to_depth_camera(sensor->depth.data.image, sensor->color.data.image);
  if(!color_from_depth || !color_from_depth.is_valid()){
    return;
  }

  //Get specific information
  float timestamp = sensor->color.data.timestamp;
  string format = sensor->color.data.format;
  this->retrieve_data_from_capture(color_from_depth, sensor->color.data_to_depth.buffer, format);

  //Fill data structure
  sensor->color.data_to_depth.image = color_from_depth;
  sensor->color.data_to_depth.name = "color_to_depth";
  sensor->color.data_to_depth.size = sensor->color.data_to_depth.buffer.size();
  sensor->color.data_to_depth.width = color_from_depth.get_width_pixels();
  sensor->color.data_to_depth.height = color_from_depth.get_height_pixels();
  sensor->color.data_to_depth.format = format;
  sensor->color.data_to_depth.timestamp = timestamp;

  //---------------------------
  color_from_depth.reset();
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
