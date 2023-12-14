#include "Data.h"


namespace eng::kinect::data{

//Constructor / Destructor
Data::Data(){
  //---------------------------


  //---------------------------
}
Data::~Data(){}

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

//Subfunction
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
  k4a_device->depth.image.width = depth.get_width_pixels();
  k4a_device->depth.image.height = depth.get_height_pixels();
  k4a_device->depth.image.format = "B8G8R8A8_SRGB";
  k4a_device->depth.image.temperature = capture.get_temperature_c();
  k4a_device->depth.image.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  depth.reset();

  //---------------------------
}
void Data::find_color(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::image color = capture.get_color_image();
  if(!color || !color.is_valid()){
    cout<<"[error] kinect color image invalid"<<endl;
    return;
  }
  k4a_device->color.image.image = color;
  k4a_device->color.image.name = "color";
  k4a_device->color.image.data = std::vector<uint8_t>(color.get_buffer(), color.get_buffer() + color.get_size());
  k4a_device->color.image.width = color.get_width_pixels();
  k4a_device->color.image.height = color.get_height_pixels();
  k4a_device->color.image.format = "B8G8R8A8_SRGB";
  k4a_device->color.image.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);
  color.reset();

  //---------------------------
}
void Data::find_color_from_depth(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::image color_from_depth = k4a_device->device.transformation.color_image_to_depth_camera(k4a_device->depth.image.image, k4a_device->color.image.image);
  if(!color_from_depth || !color_from_depth.is_valid()){
    cout<<"[error] kinect color from depth image invalid"<<endl;
    return;
  }
  k4a_device->color.image_depth.image = color_from_depth;
  k4a_device->color.image_depth.name = "color_from_depth";
  k4a_device->color.image_depth.data = std::vector<uint8_t>(color_from_depth.get_buffer(), color_from_depth.get_buffer() + color_from_depth.get_size());
  k4a_device->color.image_depth.width = color_from_depth.get_width_pixels();
  k4a_device->color.image_depth.height = color_from_depth.get_height_pixels();
  k4a_device->color.image_depth.format = "B8G8R8A8_SRGB";
  k4a_device->color.image_depth.timestamp = k4a_device->color.image.timestamp;
  color_from_depth.reset();

  for(int i=0; i<k4a_device->color.image_depth.data .size(); i++){
    k4a_device->color.image_depth.data[i] = 255;
  }



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
  k4a_device->ir.image.width = ir.get_width_pixels();
  k4a_device->ir.image.height = ir.get_height_pixels();
  k4a_device->ir.image.format = "B8G8R8A8_SRGB";
  k4a_device->ir.image.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  ir.reset();

  //---------------------------
}

}
