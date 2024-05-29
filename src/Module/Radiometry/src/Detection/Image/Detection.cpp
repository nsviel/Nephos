#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_radio);
  this->rad_glyph = new rad::detection::image::Glyph(node_radio);
  this->rad_circle = new rad::detection::image::Circle(node_radio);
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dat::base::Sensor* sensor, utl::media::Image* image){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor, image](){
    this->run_thread(sensor, image);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Detection::run_thread(dat::base::Sensor* sensor, utl::media::Image* image){
  //---------------------------

  this->detect_circle_in_image(image);
  rad_circle->draw_detected_circle();
  rad_glyph->draw_detected_sphere(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Detection::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Detection::detect_circle_in_image(utl::media::Image* image){
  //---------------------------

  cv::Mat cv_image;
  rad_image->convert_into_cv_image(image, cv_image);

  rad_circle->sphere_detection(cv_image, rad_struct->detection.cv_image);

  //---------------------------
}
void Detection::detect_rectangle_in_image(utl::media::Image* image){
  //---------------------------

  cv::Mat cv_image;
  rad_image->convert_into_cv_image(image, cv_image);
  rad_circle->sphere_detection(cv_image, rad_struct->detection.cv_image);

  //---------------------------
}

}
