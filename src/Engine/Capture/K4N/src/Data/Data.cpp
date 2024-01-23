#include "Data.h"


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
void Data::find_data_from_capture(eng::k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  //---------------------------

  //Capture data
  this->find_depth(k4n_sensor, capture);
  this->find_color(k4n_sensor, capture);
  this->find_ir(k4n_sensor, capture);

  //Finish
  k4n_sensor->master->player.ts_cur = k4n_sensor->color.image.timestamp;
  k4n_sensor->param.data_ready = true;

  //---------------------------
}

//Data function
void Data::find_depth(eng::k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  k4a::image depth = capture.get_depth_image();
  //---------------------------

  //Get specific information
  if(!depth || !depth.is_valid()){
    cout<<"[error] kinect depth image invalid"<<endl;
    return;
  }
  float timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(depth.get_format());
  this->retrieve_data_from_capture(depth, k4n_sensor->depth.image.data, format);

  //Fill data structure
  k4n_sensor->depth.image.name = "depth";
  k4n_sensor->depth.image.size = k4n_sensor->depth.image.data.size();
  k4n_sensor->depth.image.width = depth.get_width_pixels();
  k4n_sensor->depth.image.height = depth.get_height_pixels();
  k4n_sensor->depth.image.format = format;
  k4n_sensor->depth.image.temperature = capture.get_temperature_c();
  k4n_sensor->depth.image.timestamp = timestamp;
  k4n_sensor->depth.image.image = depth;

  //---------------------------
  depth.reset();
}
void Data::find_color(eng::k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  k4a::image color = capture.get_color_image();
  //---------------------------

  //Get specific information
  if(!color || !color.is_valid()){
    return;
  }
  float timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(color.get_format());
  this->retrieve_data_from_capture(color, k4n_sensor->color.image.data, format);

  //Fill data structure
  k4n_sensor->color.image.image = color;
  k4n_sensor->color.image.name = "color";
  k4n_sensor->color.image.size = k4n_sensor->color.image.data.size();
  k4n_sensor->color.image.width = color.get_width_pixels();
  k4n_sensor->color.image.height = color.get_height_pixels();
  k4n_sensor->color.image.format = format;
  k4n_sensor->color.image.timestamp = timestamp;

  //---------------------------
  color.reset();
}
void Data::find_ir(eng::k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  k4a::image ir = capture.get_ir_image();
  //---------------------------

  //Get specific information
  if(!ir || !ir.is_valid()){
    cout<<"[error] kinect ir image invalid"<<endl;
    return;
  }
  float timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  string format = retrieve_format_from_k4a(ir.get_format());
  this->retrieve_data_from_capture(ir, k4n_sensor->ir.image.data, format);

  //Fill data structure
  k4n_sensor->ir.image.image = ir;
  k4n_sensor->ir.image.name = "ir";
  k4n_sensor->ir.image.size = k4n_sensor->ir.image.data.size();
  k4n_sensor->ir.image.width = ir.get_width_pixels();
  k4n_sensor->ir.image.height = ir.get_height_pixels();
  k4n_sensor->ir.image.format = format;
  k4n_sensor->ir.image.timestamp = timestamp;

  //---------------------------
  ir.reset();
}
void Data::find_color_from_depth(eng::k4n::dev::Sensor* k4n_sensor, k4a::capture capture, k4a::transformation& transformation){
  if(!k4n_sensor->color.image.image || !k4n_sensor->depth.image.image) return;
  //---------------------------

  //Convert it into a depth POV representation
  k4a::image color_from_depth = transformation.color_image_to_depth_camera(k4n_sensor->depth.image.image, k4n_sensor->color.image.image);
  if(!color_from_depth || !color_from_depth.is_valid()){
    return;
  }

  //Get specific information
  float timestamp = k4n_sensor->color.image.timestamp;
  string format = k4n_sensor->color.image.format;
  this->retrieve_data_from_capture(color_from_depth, k4n_sensor->color.image_depth.data, format);

  //Fill data structure
  k4n_sensor->color.image_depth.image = color_from_depth;
  k4n_sensor->color.image_depth.name = "color_from_depth";
  k4n_sensor->color.image_depth.size = k4n_sensor->color.image_depth.data.size();
  k4n_sensor->color.image_depth.width = color_from_depth.get_width_pixels();
  k4n_sensor->color.image_depth.height = color_from_depth.get_height_pixels();
  k4n_sensor->color.image_depth.format = format;
  k4n_sensor->color.image_depth.timestamp = timestamp;

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
    format = "R8G8B8A8_SRGB";
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
k4a::image Data::retrieve_image_from_capture(k4a::image& image){
  k4a::image new_image;
  //---------------------------

  string format = retrieve_format_from_k4a(image.get_format());
  if(format == "R8G8B8A8_SRGB"){
    new_image = image;
  }else if(format == "MJPEG"){
    int width = image.get_width_pixels();
    int height = image.get_height_pixels();
    int size = image.get_size();
    uint8_t* mpeg = image.get_buffer();
    new_image = k4a::image::create_from_buffer(K4A_IMAGE_FORMAT_COLOR_BGRA32, width, height, width * 4, mpeg, size, nullptr, nullptr);
  }

  //---------------------------
  return new_image;
}
void Data::retrieve_data_from_capture(k4a::image& image, vector<uint8_t>& data, string& format){
  //---------------------------

  if(format == "MJPEG"){
    this->retrieve_bgra_from_mjpeg(image, data);
    format = "R8G8B8A8_SRGB";
  }else{
    data = std::vector<uint8_t>(image.get_buffer(), image.get_buffer() + image.get_size());
    format = "R8G8B8A8_SRGB";
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
