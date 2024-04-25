#include "Identification.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio::detection{

//Constructor / Destructor
Identification::Identification(radio::Structure* radio_struct){
  //---------------------------

  this->radio_struct = radio_struct;
  //this->k4n_pool = node_k4n->get_k4n_pool();

  //---------------------------
}
Identification::~Identification(){}

//Main function
void Identification::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  //k4n_pool->add_task(task_function);

  //---------------------------
}
void Identification::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("calibration");
  //---------------------------

  tasker->loop_begin();

  tasker->task_begin("detection");
  this->make_sphere_detection(sensor);
  tasker->task_end("detection");

  tasker->loop_end();

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
void Identification::make_sphere_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detect_circle_in_image(sensor);
  this->draw_detection_image(sensor);
  this->draw_detection_glyph(sensor);

  //---------------------------
}
void Identification::detect_circle_in_image(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;
  cv::Mat cv_input;
  radio_image->convert_into_cv_image(input, cv_input);
  //sensor->detection.vec_circle = radio_hough->sphere_detection(cv_input, sensor->detection.cv_image);
  sensor->detection.nb_detection = sensor->detection.vec_circle.size();

  //---------------------------
}
void Identification::draw_detection_image(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(radio_struct->detection.hough.drawing_mode){
    case radio::hough::ALL:{
      radio_image->draw_all_sphere(sensor);
      break;
    }
    case radio::hough::BEST:{
      radio_image->draw_best_sphere(sensor);
      break;
    }
  }

  //---------------------------
}
void Identification::draw_detection_glyph(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(radio_struct->detection.hough.drawing_mode){
    case radio::hough::ALL:{
      radio_glyph->draw_all_sphere_glyph(sensor);
      break;
    }
    case radio::hough::BEST:{
      radio_glyph->draw_best_sphere_glyph(sensor);
      break;
    }
  }

  //---------------------------
}

}
