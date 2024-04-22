#include "Detector.h"

#include <K4N/Namespace.h>


namespace k4n::detection{

//Constructor / Destructor
Detector::Detector(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_glyph = new k4n::detection::Glyph(node_k4n);
  this->k4n_image = new k4n::matching::Image(node_k4n);
  this->k4n_hough = new k4n::detection::Hough(node_k4n);

  //---------------------------
}
Detector::~Detector(){}

//Main function
void Detector::make_sphere_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detect_circle_in_image(sensor);
  this->draw_detection_image(sensor);
  this->draw_detection_glyph(sensor);

  //---------------------------
}

//Subfunction
void Detector::detect_circle_in_image(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;
  cv::Mat cv_input;
  k4n_image->convert_into_cv_image(input, cv_input);
  sensor->detection.vec_circle = k4n_hough->sphere_detection(cv_input, sensor->detection.cv_image);
  sensor->detection.nb_detection = sensor->detection.vec_circle.size();

  //---------------------------
}
void Detector::draw_detection_image(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->matching.hough.drawing_mode){
    case k4n::hough::ALL:{
      k4n_image->draw_all_sphere(sensor);
      break;
    }
    case k4n::hough::BEST:{
      k4n_image->draw_best_sphere(sensor);
      break;
    }
  }

  //---------------------------
}
void Detector::draw_detection_glyph(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->matching.hough.drawing_mode){
    case k4n::hough::ALL:{
      k4n_glyph->draw_all_sphere_glyph(sensor);
      break;
    }
    case k4n::hough::BEST:{
      k4n_glyph->draw_best_sphere_glyph(sensor);
      break;
    }
  }

  //---------------------------
}

}
