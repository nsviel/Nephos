#include "Image.h"

#include <K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Image::Image(){
  //---------------------------

  this->k4a_depth = new k4n::data::Depth();
  this->k4a_infrared = new k4n::data::Infrared();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }
  this->thread = std::thread(&Image::make_images, this, sensor);

  //---------------------------
}
void Image::make_images(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  //---------------------------

  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("image");
  tasker->loop_begin();

  //Color image
  tasker->task_begin("color");
  this->copy_image_color(sensor);
  tasker->task_end("color");

  //Depth image
  tasker->task_begin("depth");
  this->copy_image_depth(sensor);
  tasker->task_end("depth");

  //Infrared image
  tasker->task_begin("infrared");
  this->copy_image_ir(sensor);
  tasker->task_end("infrared");

  tasker->loop_end();

  //---------------------------
}

//Subfunction
void Image::copy_image_color(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  //---------------------------

  image->color.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  image->color.size = image->color.data.size();
  image->color.width = sensor->color.data.width;
  image->color.height = sensor->color.data.height;
  image->color.format = sensor->color.data.format;
  image->color.new_data = true;

  //---------------------------
}
void Image::copy_image_depth(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  //---------------------------

  image->depth.data = k4a_depth->convert_depth_into_color(sensor);
  image->depth.size = image->depth.data.size();
  image->depth.width = sensor->depth.data.width;
  image->depth.height = sensor->depth.data.height;
  image->depth.format = "R8G8B8A8_SRGB";
  image->depth.new_data = true;

  //---------------------------
}
void Image::copy_image_ir(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
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
