#include "Image.h"

#include <Engine/Capture/K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace eng::k4n::data{

//Constructor / Destructor
Image::Image(){
  //---------------------------

  this->k4a_depth = new eng::k4n::data::Depth();
  this->k4a_infrared = new eng::k4n::data::Infrared();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::make_images(eng::k4n::dev::Sensor* sensor){
  prf::Tasker* profiler = sensor->tasker_cap;
  eng::k4n::structure::Image* image = &sensor->image;
  //---------------------------

  //Image data copy
  profiler->task_begin("image::data");
  this->copy_image_color(sensor);
  this->copy_image_depth(sensor);
  this->copy_image_ir(sensor);
  profiler->task_end("image::data");

  //---------------------------
}

//Subfunction
void Image::copy_image_color(eng::k4n::dev::Sensor* sensor){
  eng::k4n::structure::Image* image = &sensor->image;
  //---------------------------

  image->color.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  image->color.size = image->color.data.size();
  image->color.width = sensor->color.data.width;
  image->color.height = sensor->color.data.height;
  image->color.format = sensor->color.data.format;
  image->color.new_data = true;

  //---------------------------
}
void Image::copy_image_depth(eng::k4n::dev::Sensor* sensor){
  eng::k4n::structure::Image* image = &sensor->image;
  //---------------------------

  image->depth.data = k4a_depth->convert_depth_into_color(sensor);
  image->depth.size = image->depth.data.size();
  image->depth.width = sensor->depth.data.width;
  image->depth.height = sensor->depth.data.height;
  image->depth.format = "R8G8B8A8_SRGB";
  image->depth.new_data = true;

  //---------------------------
}
void Image::copy_image_ir(eng::k4n::dev::Sensor* sensor){
  eng::k4n::structure::Image* image = &sensor->image;
  //---------------------------

  image->ir.data = k4a_infrared->convert_ir_into_color(sensor);
  image->ir.size = image->ir.data.size();
  image->ir.width = sensor->ir.data.width;
  image->ir.height = sensor->ir.data.height;
  image->ir.format = "R8G8B8A8_SRGB";
  image->ir.new_data = true;

  //---------------------------
}

}
