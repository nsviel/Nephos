#include "Image.h"

#include <Engine/Capture/K4N/Namespace.h>


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
  utl::element::Profiler* profiler = sensor->cap_profiler;
  eng::k4n::structure::Image* image = &sensor->image;
  //---------------------------

  profiler->task_begin("image::lock");
  std::unique_lock<std::mutex> lock(image->mutex);
  profiler->task_end("image::lock");

  //Image data copy

  //---------------------------
}

}
