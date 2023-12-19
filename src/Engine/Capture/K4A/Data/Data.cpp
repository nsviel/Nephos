#include "Data.h"


namespace eng::kinect::data{

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
void Data::find_data_from_capture(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  this->find_depth(k4a_device, capture);
  this->find_color(k4a_device, capture);
  this->find_color_from_depth(k4a_device, capture);
  this->find_ir(k4a_device, capture);
  k4a_device->device.data_ready = true;

  //---------------------------
}

//Data function
void Data::find_depth(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::image depth = capture.get_depth_image();
  if(!depth || !depth.is_valid()){
    cout<<"[error] kinect depth image invalid"<<endl;
    return;
  }
  k4a_device->depth.image.image = depth;
  k4a_device->depth.image.name = "depth";
  k4a_device->depth.image.data = std::vector<uint8_t>(depth.get_buffer(), depth.get_buffer() + depth.get_size());
  k4a_device->depth.image.size = depth.get_size();
  k4a_device->depth.image.width = depth.get_width_pixels();
  k4a_device->depth.image.height = depth.get_height_pixels();
  k4a_device->depth.image.format = convert_k4a_format(depth.get_format());
  k4a_device->depth.image.temperature = capture.get_temperature_c();
  k4a_device->depth.image.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  depth.reset();

  //---------------------------
}
void Data::find_color(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::image color = capture.get_color_image();
  if(!color || !color.is_valid()){
    return;
  }
  k4a_device->color.image.image = color;
  k4a_device->color.image.name = "color";
  k4a_device->color.image.data = retrieve_data_from_capture(color);
  k4a_device->color.image.size = color.get_size();
  k4a_device->color.image.width = color.get_width_pixels();
  k4a_device->color.image.height = color.get_height_pixels();
  k4a_device->color.image.format = "B8G8R8A8_SRGB";
  k4a_device->color.image.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);
  k4a_device->player.ts_cur = k4a_device->color.image.timestamp;

  //---------------------------
  color.reset();
}
void Data::find_color_from_depth(K4A_device* k4a_device, k4a::capture capture){
  if(!k4a_device->color.image.image || !k4a_device->depth.image.image) return;
  //---------------------------
/*
  //Creat a new k4a image with RGBA data format
  int width = k4a_device->color.image.width;
  int height = k4a_device->color.image.height;
  int size = k4a_device->color.image.size;
  vector<uint8_t> data = k4a_device->color.image.data;
  k4a::image new_image = k4a::image::create_from_buffer(K4A_IMAGE_FORMAT_COLOR_BGRA32, width, height, width * 4, data.data(), size, nullptr, nullptr);

  //Convert it into a depth POV representation
  k4a::image color_from_depth = k4a_device->device.transformation.color_image_to_depth_camera(k4a_device->depth.image.image, k4a_device->color.image.image);
  if(!color_from_depth || !color_from_depth.is_valid()){
    return;
  }
  k4a_device->color.image_depth.image = color_from_depth;
  k4a_device->color.image_depth.name = "color_from_depth";
  k4a_device->color.image_depth.data = retrieve_data_from_capture(color_from_depth);
  k4a_device->color.image_depth.size = color_from_depth.get_size();
  k4a_device->color.image_depth.width = color_from_depth.get_width_pixels();
  k4a_device->color.image_depth.height = color_from_depth.get_height_pixels();
  k4a_device->color.image_depth.format = "B8G8R8A8_SRGB";
  k4a_device->color.image_depth.timestamp = k4a_device->color.image.timestamp;
  color_from_depth.reset();
*/
  //---------------------------
}
void Data::find_ir(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::image ir = capture.get_ir_image();
  if(!ir || !ir.is_valid()){
    cout<<"[error] kinect ir image invalid"<<endl;
    return;
  }
  k4a_device->ir.image.image = ir;
  k4a_device->ir.image.name = "ir";
  k4a_device->ir.image.data = std::vector<uint8_t>(ir.get_buffer(), ir.get_buffer() + ir.get_size());
  k4a_device->ir.image.size = ir.get_size();
  k4a_device->ir.image.width = ir.get_width_pixels();
  k4a_device->ir.image.height = ir.get_height_pixels();
  k4a_device->ir.image.format = convert_k4a_format(ir.get_format());
  k4a_device->ir.image.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  ir.reset();

  //---------------------------
}

//Subfunction
string Data::convert_k4a_format(k4a_image_format_t color_format){
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
k4a::image Data::retrieve_image_from_capture(k4a::image& image){
  k4a::image new_image;
  //---------------------------

  string format = convert_k4a_format(image.get_format());
  if(format == "B8G8R8A8_SRGB"){
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
vector<uint8_t> Data::retrieve_data_from_capture(k4a::image& image){
  std::vector<uint8_t> data;
  //---------------------------

  string format = convert_k4a_format(image.get_format());
  if(format == "B8G8R8A8_SRGB"){
    data = std::vector<uint8_t>(image.get_buffer(), image.get_buffer() + image.get_size());
  }else if(format == "MJPEG"){
    data = convert_mjpeg_image(image);
  }

  //---------------------------
  return data;
}
vector<uint8_t> Data::convert_mjpeg_image(k4a::image& image){
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

  //---------------------------
  return bgra;
}


}
