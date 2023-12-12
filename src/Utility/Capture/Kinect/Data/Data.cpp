#include "Data.h"


namespace util::kinect::data{

//Constructor / Destructor
Data::Data(){
  //---------------------------


  //---------------------------
}
Data::~Data(){}

//Main function
void Data::find_data_from_capture(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  this->find_color(&k4a_device->data, capture);
  this->find_depth(&k4a_device->data, capture);
  this->find_ir(&k4a_device->data, capture);
  k4a_device->device.data_ready = true;

  //---------------------------
}

//Subfunction
void Data::find_color(util::kinect::structure::Data* data, k4a::capture capture){
  //---------------------------

  k4a::image color = capture.get_color_image();
  if (!color || !color.is_valid()) {return;}
  data->color.name = "color";
  data->color.buffer = color.get_buffer();
  data->color.size = color.get_size();
  data->color.width = color.get_width_pixels();
  data->color.height = color.get_height_pixels();
  data->color.format = "B8G8R8A8_SRGB";
  data->color.timestamp = static_cast<float>(color.get_device_timestamp().count() / 1000000.0f);
  color.reset();

  //---------------------------
}
void Data::find_depth(util::kinect::structure::Data* data, k4a::capture capture){
  //---------------------------

  k4a::image depth = capture.get_depth_image();
  if (!depth || !depth.is_valid()) {return;}
  data->depth.name = "depth";
  data->depth.buffer = depth.get_buffer();
  data->depth.size = depth.get_size();
  data->depth.width = depth.get_width_pixels();
  data->depth.height = depth.get_height_pixels();
  data->depth.format = "B8G8R8A8_SRGB";
  data->depth.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  depth.reset();

  //---------------------------
}
void Data::find_ir(util::kinect::structure::Data* data, k4a::capture capture){
  //---------------------------

  k4a::image ir = capture.get_ir_image();
  if (!ir || !ir.is_valid()) {return;}
  data->ir.name = "ir";
  data->ir.buffer = ir.get_buffer();
  data->ir.size = ir.get_size();
  data->ir.width = ir.get_width_pixels();
  data->ir.height = ir.get_height_pixels();
  data->ir.format = "B8G8R8A8_SRGB";
  data->ir.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  ir.reset();

  //---------------------------
}

}
