#include "Circle.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Circle::Circle(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_radio);

  this->find_hough_parameter(rad::hough::GRADIENT_ALT);

  //---------------------------
}
Circle::~Circle(){}

//Main function
void Circle::detect_circle(cv::Mat& image){
  if(image.empty()) return;
  //------------------------

  cv::Mat gray, canny;
  rad_image->convert_into_gray(image, gray);
  rad_image->apply_canny(gray, canny);
  this->compute_hough_circle(canny);
  this->draw_detected_circle(canny);

  //------------------------
}

//Draw function
void Circle::draw_detected_circle(cv::Mat& image){
  //---------------------------

  switch(rad_struct->detection.hough.drawing_mode){
    case rad::hough::ALL:{
      this->draw_all_circle(image);
      break;
    }
    case rad::hough::BEST:{
      this->draw_best_circle(image);
      break;
    }
  }

  //---------------------------
}
void Circle::draw_all_circle(cv::Mat& image){
  if(image.empty()) return;
  //------------------------

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);
  rad_image->draw_circle(result, rad_struct->detection.vec_circle);
  rad_image->draw_bounding_box(result);
  rad_image->convert_into_subimage(result);
  rad_image->convert_into_utl_image(result, &rad_struct->detection.image);

  //------------------------
}
void Circle::draw_best_circle(cv::Mat& image){
  if(image.empty()) return;
  //------------------------

  vector<rad::detection::structure::Circle> vec_circle;
  if(rad_struct->detection.vec_circle.size() > 0){
    vec_circle.push_back(rad_struct->detection.vec_circle[0]);
  }

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);
  rad_image->draw_circle(result, vec_circle);
  rad_image->draw_bounding_box(result);
  rad_image->convert_into_subimage(result);
  rad_image->convert_into_utl_image(result, &rad_struct->detection.image);

  //------------------------
}

//Hough function
void Circle::compute_hough_circle(cv::Mat& image){
  //---------------------------

  std::vector<cv::Vec3f> circles;
  int& mode = rad_struct->detection.hough.cv_mode;
  int& ratio = rad_struct->detection.hough.ratio;
  int& min_dist = rad_struct->detection.hough.min_dist;
  int& min_radius = rad_struct->detection.hough.min_radius;
  int& max_radius = rad_struct->detection.hough.max_radius;
  float& param_1 = rad_struct->detection.hough.param_1;
  float& param_2 = rad_struct->detection.hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  vector<rad::detection::structure::Circle> vec_circle;
  for(int i=0; i<circles.size(); i++){
    rad::detection::structure::Circle circle;
    circle.center = glm::ivec2(circles[i][0], circles[i][1]);
    circle.radius = circles[i][2];
    vec_circle.push_back(circle);
  }

  rad_struct->detection.vec_circle = vec_circle;
  rad_struct->detection.nb_detection = vec_circle.size();

  //---------------------------
}
void Circle::find_hough_parameter(int mode){
  //---------------------------

  switch(mode){
    case rad::hough::GRADIENT:{
      rad_struct->detection.hough.param_1 = 100; //higher threshold for the Canny edge detector
      rad_struct->detection.hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      rad_struct->detection.hough.cv_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case rad::hough::GRADIENT_ALT:{
      rad_struct->detection.hough.param_1 = 300;
      rad_struct->detection.hough.param_2 = 0.9;
      rad_struct->detection.hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
      break;
    }
  }

  //---------------------------
}


}
