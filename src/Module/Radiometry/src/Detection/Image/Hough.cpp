#include "Hough.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Hough::Hough(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  this->find_mode_parameter(rad::hough::GRADIENT_ALT);

  //---------------------------
}
Hough::~Hough(){}

//Main function
vector<rad::structure::Circle> Hough::sphere_detection(cv::Mat& input, cv::Mat& output){
  vec_circle.clear();
  if(input.empty()) return vec_circle;
  //------------------------

  //Pre processing
  this->preprocessing(input, output);

  // Perform Hough Transform to detect lines
  this->compute_hough_circle(output);

  //------------------------
  return vec_circle;
}

//Subfunction
void Hough::preprocessing(cv::Mat& input, cv::Mat& output){
  //---------------------------

  if(rad_struct->detection.canny.apply){
    // Perform canny edge detection
    int& thresh_lower = rad_struct->detection.canny.lower_threshold;
    int& thresh_upper = rad_struct->detection.canny.upper_threshold;
    cv::Canny(input, output, thresh_lower, thresh_upper);
  }else{
    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);
  }

  //---------------------------
}
void Hough::compute_hough_circle(cv::Mat& image){
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

  for(int i=0; i<circles.size(); i++){
    rad::structure::Circle circle;
    circle.center = glm::ivec2(circles[i][0], circles[i][1]);
    circle.radius = circles[i][2];
    vec_circle.push_back(circle);
  }

  //---------------------------
}
void Hough::find_mode_parameter(int mode){
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
