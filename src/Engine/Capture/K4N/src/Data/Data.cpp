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
  this->find_color_to_depth(sensor, capture, sensor->param.transformation);
  this->find_ir(sensor, capture);


  //Finish
  sensor->master->player.ts_cur = sensor->color.image.timestamp;
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
  this->retrieve_data_from_capture(depth, sensor->depth.image.buffer, format);

  //Fill data structure
  sensor->depth.image.name = "depth";
  sensor->depth.image.size = sensor->depth.image.buffer.size();
  sensor->depth.image.width = depth.get_width_pixels();
  sensor->depth.image.height = depth.get_height_pixels();
  sensor->depth.image.format = format;
  sensor->depth.image.temperature = capture.get_temperature_c();
  sensor->depth.image.timestamp = timestamp;
  sensor->depth.image.image = depth;

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
  this->retrieve_data_from_capture(color, sensor->color.image.buffer, format);

  //Fill data structure
  sensor->color.image.image = color;
  sensor->color.image.name = "color";
  sensor->color.image.size = sensor->color.image.buffer.size();
  sensor->color.image.width = color.get_width_pixels();
  sensor->color.image.height = color.get_height_pixels();
  sensor->color.image.format = format;
  sensor->color.image.timestamp = timestamp;

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
  this->retrieve_data_from_capture(ir, sensor->ir.image.buffer, format);

  //Fill data structure
  sensor->ir.image.image = ir;
  sensor->ir.image.name = "ir";
  sensor->ir.image.size = sensor->ir.image.buffer.size();
  sensor->ir.image.width = ir.get_width_pixels();
  sensor->ir.image.height = ir.get_height_pixels();
  sensor->ir.image.format = format;
  sensor->ir.image.timestamp = timestamp;

  //---------------------------
  ir.reset();
}

//Transformed data
void Data::find_depth_to_color(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.image.image || !sensor->depth.image.image) return;
  //---------------------------
/*
  //Convert it into a depth POV representation
  transformation.depth_image_to_color_camera(sensor->depth.image.image, sensor->depth.image.image_to_color);
  if(!sensor->depth.image.image_to_color || !sensor->depth.image.image_to_color.is_valid()){
    return;
  }

  //Get specific information
  float timestamp = sensor->depth.image.timestamp;
  string format = sensor->depth.image.format;
  this->retrieve_data_from_capture(sensor->depth.image.image_to_color, sensor->depth.image_to_color.data, format);

  //Fill data structure
  sensor->color.image_to_depth.name = "depth_to_color";
  sensor->color.image_to_depth.size = sensor->color.image_to_depth.buffer.size();
  sensor->color.image_to_depth.width = color_from_depth.get_width_pixels();
  sensor->color.image_to_depth.height = color_from_depth.get_height_pixels();
  sensor->color.image_to_depth.format = format;
  sensor->color.image_to_depth.timestamp = timestamp;

  //---------------------------
  color_from_depth.reset();*/
}
void Data::find_color_to_depth(eng::k4n::dev::Sensor* sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!sensor->color.image.image || !sensor->depth.image.image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_from_depth = transformation.color_image_to_depth_camera(sensor->depth.image.image, sensor->color.image.image);
  if(!color_from_depth || !color_from_depth.is_valid()){
    return;
  }

  //Get specific information
  float timestamp = sensor->color.image.timestamp;
  string format = sensor->color.image.format;
  this->retrieve_data_from_capture(color_from_depth, sensor->color.image_to_depth.buffer, format);

  //Fill data structure
  sensor->color.image_to_depth.image = color_from_depth;
  sensor->color.image_to_depth.name = "color_to_depth";
  sensor->color.image_to_depth.size = sensor->color.image_to_depth.buffer.size();
  sensor->color.image_to_depth.width = color_from_depth.get_width_pixels();
  sensor->color.image_to_depth.height = color_from_depth.get_height_pixels();
  sensor->color.image_to_depth.format = format;
  sensor->color.image_to_depth.timestamp = timestamp;

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
