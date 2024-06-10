#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Detection::Detection(rad::detection::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_detection);
  this->rad_glyph = new rad::detection::glyph::Manager(node_detection);
  this->rad_circle = new rad::detection::image::Circle(node_detection);
  this->thread_pool = node_engine->get_thread_pool();
  this->ope_image = new ope::image::Manager();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Detection::run_thread(dyn::base::Sensor* sensor){
  utl::media::Image* image = ope_image->get_image(sensor, utl::media::INTENSITY);
  //---------------------------

  if(image != nullptr && image->new_data){
    this->make_shape_detection(sensor, image);
  }

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
void Detection::make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image){
  //---------------------------

  cv::Mat cv_image, gray, canny;
  rad_image->convert_into_cv_image(image, cv_image);
  rad_image->convert_into_gray(cv_image, gray);
  rad_image->apply_canny(gray, canny);

  rad_circle->detect_circle(canny);
  rad_glyph->draw_detection_sphere(sensor);

  //---------------------------
}

}
