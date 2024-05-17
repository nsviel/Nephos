#include "Identification.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Identification::Identification(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_image = new rad::detection::utils::Image(node_radio);
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Identification::~Identification(){}

//Main function
void Identification::start_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Identification::run_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->make_sphere_detection(sensor);

  //---------------------------
  this->idle = true;
}
void Identification::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Identification::make_sphere_detection(dat::base::Sensor* sensor){
  //---------------------------

  this->detect_circle_in_image(sensor);
  this->draw_detection_image(sensor);
  this->draw_detection_glyph(sensor);

  //---------------------------
}
void Identification::detect_circle_in_image(dat::base::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->ir.image;
  cv::Mat cv_input;
  rad_image->convert_into_cv_image(input, cv_input);
  //rad_struct->detection.vec_circle = rad_hough->sphere_detection(cv_input, rad_struct->detection.cv_image);
  rad_struct->detection.nb_detection = rad_struct->detection.vec_circle.size();

  //---------------------------
}
void Identification::draw_detection_image(dat::base::Sensor* sensor){
  //---------------------------

  switch(rad_struct->detection.hough.drawing_mode){
    case rad::hough::ALL:{
      rad_image->draw_all_sphere(sensor);
      break;
    }
    case rad::hough::BEST:{
      rad_image->draw_best_sphere(sensor);
      break;
    }
  }

  //---------------------------
}
void Identification::draw_detection_glyph(dat::base::Sensor* sensor){
  //---------------------------

  switch(rad_struct->detection.hough.drawing_mode){
    case rad::hough::ALL:{
      rad_glyph->draw_all_sphere_glyph(sensor);
      break;
    }
    case rad::hough::BEST:{
      rad_glyph->draw_best_sphere_glyph(sensor);
      break;
    }
  }

  //---------------------------
}

}
