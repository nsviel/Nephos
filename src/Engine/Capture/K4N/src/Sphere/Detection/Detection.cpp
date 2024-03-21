#include "Detection.h"

#include <K4N/Namespace.h>


namespace k4n::registration{

//Constructor / Destructor
Detection::Detection(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_glyph = new k4n::calibration::Glyph(node_k4n);
  this->k4n_image = new k4n::calibration::Image(node_k4n);
  this->k4n_hough = new k4n::calibration::Hough(node_k4n);
  
  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::make_sphere_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detect_circle_in_image(sensor);
  k4n_glyph->draw_glyph(sensor);

  //---------------------------
}

//Subfunction
void Detection::detect_circle_in_image(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;
  cv::Mat cv_input;
  k4n_image->convert_into_cv_image(input, cv_input);
  sensor->detection.vec_circle = k4n_hough->sphere_detection(cv_input, sensor->detection.cv_image);
  sensor->detection.nb_detection = sensor->detection.vec_circle.size();

  //---------------------------
}

}
