#include "Image.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Operation/Namespace.h>
#include <Radiometry/Namespace.h>

namespace k4n::processing{

//Constructor / Destructor
Image::Image(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  rad::Node* node_radio = node_k4n->get_node_radio();

  this->k4n_data = new k4n::utils::Data();
  this->k4n_config = new k4n::utils::Configuration();
  this->radio_identification = node_radio->get_radio_identification();
  this->thread_pool = node_engine->get_thread_pool();

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
  thread_pool->add_task(task_function);

  //---------------------------
}
void Image::run_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->copy_image(sensor);

  //Encode image as texture
  //radio_identification->start_thread(sensor);

  //---------------------------
  this->idle = true;
}
void Image::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  //radio_identification->wait_thread();

  //---------------------------
}

//Subfunction
void Image::copy_image(k4n::dev::Sensor* sensor){
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

  sensor->color.image.data = std::vector<uint8_t>(sensor->color.data.buffer, sensor->color.data.buffer + sensor->color.data.size);
  sensor->color.image.size = sensor->color.image.data.size();
  sensor->color.image.width = sensor->color.data.width;
  sensor->color.image.height = sensor->color.data.height;
  sensor->color.image.format = sensor->color.data.format;

  if(sensor->color.image.data.size() != sensor->color.data.size){
    sensor->color.image.new_data = false;
  }else{
    sensor->color.image.new_data = true;
  }

  sensor->bind_image(&sensor->color.image);

  //---------------------------
}
void Image::copy_image_depth(k4n::dev::Sensor* sensor){
  //---------------------------

  k4n_data->convert_depth_into_color(sensor, sensor->depth.image.data);
  sensor->depth.image.size = sensor->depth.image.data.size();
  sensor->depth.image.width = sensor->depth.data.width;
  sensor->depth.image.height = sensor->depth.data.height;
  sensor->depth.image.format = "R8G8B8A8_SRGB";
  sensor->depth.image.new_data = true;

  sensor->bind_image(&sensor->depth.image);

  //---------------------------
}
void Image::copy_image_ir(k4n::dev::Sensor* sensor){
  //---------------------------

  k4n_data->convert_ir_into_color(sensor, sensor->ir.image.data);
  sensor->ir.image.size = sensor->ir.image.data.size();
  sensor->ir.image.width = sensor->ir.data.width;
  sensor->ir.image.height = sensor->ir.data.height;
  sensor->ir.image.format = "R8G8B8A8_SRGB";
  sensor->ir.image.new_data = true;

  sensor->bind_image(&sensor->ir.image);

  //---------------------------
}

}
