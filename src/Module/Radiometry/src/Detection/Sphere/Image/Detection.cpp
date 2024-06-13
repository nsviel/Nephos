#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Detection::Detection(rad::detection::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  eng::Node* node_engine = node_radio->get_node_engine();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_detection);
  this->rad_glyph = new rad::detection::sphere::Glyph(node_detection);
  this->rad_hough = new rad::detection::image::Hough(node_detection);
  this->thread_pool = node_engine->get_thread_pool();
  this->dat_image = node_data->get_dat_image();

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
  static float current_timestamp = 0;
  //---------------------------

  if(sensor != nullptr){
    utl::media::Image* image = dat_image->get_image(sensor, utl::media::INTENSITY);

    if(image != nullptr && image->timestamp != current_timestamp){
      current_timestamp = image->timestamp;
      this->make_shape_detection(sensor, image);
    }
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
  utl::media::Image* output = dat_image->get_or_create_image(sensor, utl::media::RADIOMETRY);
  output->timestamp = image->timestamp;
  //---------------------------

  cv::Mat cv_image, gray, canny;
  rad_image->convert_into_cv_image(image, cv_image);
  if(cv_image.empty()) return;
  
  rad_image->convert_into_gray(cv_image, gray);
  rad_image->apply_canny(gray, canny);

  rad_hough->detect_circle(canny, output);
  rad_glyph->draw_detection_sphere(sensor);

  //---------------------------
}

}
