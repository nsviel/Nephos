#include "Hough.h"

#include <K4N/Namespace.h>
#include <Radiometry/Namespace.h>

namespace radio::detection{

//Constructor / Destructor
Hough::Hough(radio::Structure* radio_struct){
  //---------------------------

  this->radio_struct = radio_struct;

  this->find_mode_parameter(radio::hough::GRADIENT_ALT);

  //---------------------------
}
Hough::~Hough(){}

//Main function
vector<radio::structure::Circle> Hough::sphere_detection(cv::Mat& input, cv::Mat& output){
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

  if(radio_struct->detection.canny.apply){
    // Perform canny edge detection
    int& thresh_lower = radio_struct->detection.canny.lower_threshold;
    int& thresh_upper = radio_struct->detection.canny.upper_threshold;
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
  int& mode = radio_struct->detection.hough.cv_mode;
  int& ratio = radio_struct->detection.hough.ratio;
  int& min_dist = radio_struct->detection.hough.min_dist;
  int& min_radius = radio_struct->detection.hough.min_radius;
  int& max_radius = radio_struct->detection.hough.max_radius;
  float& param_1 = radio_struct->detection.hough.param_1;
  float& param_2 = radio_struct->detection.hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  for(int i=0; i<circles.size(); i++){
    radio::structure::Circle circle;
    circle.center = glm::ivec2(circles[i][0], circles[i][1]);
    circle.radius = circles[i][2];
    vec_circle.push_back(circle);
  }

  //---------------------------
}
void Hough::find_mode_parameter(int mode){
  //---------------------------

  switch(mode){
    case radio::hough::GRADIENT:{
      radio_struct->detection.hough.param_1 = 100; //higher threshold for the Canny edge detector
      radio_struct->detection.hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      radio_struct->detection.hough.cv_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case radio::hough::GRADIENT_ALT:{
      radio_struct->detection.hough.param_1 = 300;
      radio_struct->detection.hough.param_2 = 0.9;
      radio_struct->detection.hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
      break;
    }
  }

  //---------------------------
}


}
