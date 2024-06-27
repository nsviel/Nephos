#include "Hough.h"

#include <Radiometry/Namespace.h>


namespace rad::correction::image{

//Constructor / Destructor
Hough::Hough(rad::correction::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_image = new rad::correction::image::Image(node_correction);

  this->set_hough_mode(rad::hough::GRADIENT_ALT);

  //---------------------------
}
Hough::~Hough(){}

//Main function
void Hough::detect_circle(cv::Mat& image, utl::media::Image* output){
  if(image.empty()) return;
  //------------------------

  this->compute_hough_circle(image);
  this->draw_detected_circle(image, output);

  //------------------------
}

//Hough function
void Hough::compute_hough_circle(cv::Mat& image){
  //---------------------------

  std::vector<cv::Vec3f> circles;
  int& mode = rad_struct->hough.cv_mode;
  int& ratio = rad_struct->hough.ratio;
  int& min_dist = rad_struct->hough.min_dist;
  int& min_radius = rad_struct->hough.min_radius;
  int& max_radius = rad_struct->hough.max_radius;
  float& param_1 = rad_struct->hough.param_1;
  float& param_2 = rad_struct->hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  std::vector<rad::correction::structure::Circle> vec_circle;
  for(int i=0; i<circles.size(); i++){
    rad::correction::structure::Circle circle;
    circle.center = glm::ivec2(circles[i][0], circles[i][1]);
    circle.radius = circles[i][2];
    vec_circle.push_back(circle);
  }

  rad_struct->hough.vec_circle = vec_circle;
  rad_struct->hough.nb_detection = vec_circle.size();

  //---------------------------
}
void Hough::set_hough_mode(int mode){
  //---------------------------

  switch(mode){
    case rad::hough::GRADIENT:{
      rad_struct->hough.param_1 = 100; //higher threshold for the Canny edge detector
      rad_struct->hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      rad_struct->hough.cv_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case rad::hough::GRADIENT_ALT:{
      rad_struct->hough.param_1 = 300;
      rad_struct->hough.param_2 = 0.9;
      rad_struct->hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
      break;
    }
  }

  //---------------------------
}

//Draw function
void Hough::draw_detected_circle(cv::Mat& image, utl::media::Image* output){
  //---------------------------

  switch(rad_struct->hough.draw){
    case rad::hough::ALL:{
      this->draw_all_circle(image, output);
      break;
    }
    case rad::hough::BEST:{
      this->draw_best_circle(image, output);
      break;
    }
  }

  //---------------------------
}
void Hough::draw_all_circle(cv::Mat& image, utl::media::Image* output){
  if(image.empty()) return;
  //------------------------

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);
  rad_image->draw_circle(result, rad_struct->hough.vec_circle);
  rad_image->draw_bounding_box(result);
  rad_image->convert_into_utl_image(result, output);

  //------------------------
}
void Hough::draw_best_circle(cv::Mat& image, utl::media::Image* output){
  if(image.empty()) return;
  //------------------------

  std::vector<rad::correction::structure::Circle> vec_circle;
  if(rad_struct->hough.vec_circle.size() > 0){
    vec_circle.push_back(rad_struct->hough.vec_circle[0]);
  }

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);
  rad_image->draw_circle(result, vec_circle);
  rad_image->draw_bounding_box(result);
  rad_image->convert_into_utl_image(result, output);

  //------------------------
}

}
