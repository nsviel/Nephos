#include "Image.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Operation/Namespace.h>
#include <Radiometry/Namespace.h>

namespace k4n::processing{

//Constructor / Destructor
Image::Image(k4n::Node* node_k4n){
  //---------------------------

  radio::Node* node_radio = node_k4n->get_node_radio();

  this->k4n_depth = new k4n::data::Depth();
  this->k4n_infrared = new k4n::data::Infrared();
  this->k4n_config = new k4n::config::Configuration();
  this->radio_identification = node_radio->get_radio_identification();
  this->k4n_pool = node_k4n->get_k4n_pool();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::start_thread(k4n::dev::Sensor* sensor){
  if(sensor->profiler == nullptr) return;
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Image::run_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->copy_image(sensor);

  //Encode image as texture
  radio_identification->start_thread(sensor);

  //---------------------------
  this->idle = true;
}
void Image::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  radio_identification->wait_thread();

  //---------------------------
}

//Subfunction
void Image::copy_image(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("image");
  //---------------------------

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
void Image::copy_image_color(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  //---------------------------

  /*
  string resolution = k4n_config->find_mode_color_resolution(sensor->color.config.resolution);

  //If color resolution is too big, display transformed color image - to be changed
  if(resolution == "2160p" || resolution == "3072p"){
    sensor->color.data.buffer = sensor->color.cloud.buffer;
    sensor->color.data.size = sensor->color.cloud.size;
    sensor->color.data.width = sensor->color.cloud.width;
    sensor->color.data.height = sensor->color.cloud.height;
    sensor->color.data.format = sensor->color.cloud.format;
  }
  */

  image->color.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  image->color.size = image->color.data.size();
  image->color.width = sensor->color.data.width;
  image->color.height = sensor->color.data.height;
  image->color.format = sensor->color.data.format;

  if(image->color.data.size() != sensor->color.data.size){
    image->color.new_data = false;
  }else{
    image->color.new_data = true;
  }


  //---------------------------
}
void Image::copy_image_depth(k4n::dev::Sensor* sensor){
  k4n::structure::Image* image = &sensor->image;
  //---------------------------

  k4n_depth->convert_depth_into_color(sensor, image->depth.data);
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

  k4n_infrared->convert_ir_into_color(sensor, image->ir.data);
  image->ir.size = image->ir.data.size();
  image->ir.width = sensor->ir.data.width;
  image->ir.height = sensor->ir.data.height;
  image->ir.format = "R8G8B8A8_SRGB";
  image->ir.new_data = true;

  //---------------------------
}

}
