#include "Hough.h"

#include <K4N/Namespace.h>


namespace k4n::detection{

//Constructor / Destructor
Hough::Hough(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  this->find_mode_parameter(k4n::hough::ALL);

  //---------------------------
}
Hough::~Hough(){}

//Main function
vector<k4n::structure::Circle> Hough::sphere_detection(cv::Mat& input, cv::Mat& output){
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

  if(k4n_struct->matching.canny.apply){
    // Perform canny edge detection
    int& thresh_lower = k4n_struct->matching.canny.lower_threshold;
    int& thresh_upper = k4n_struct->matching.canny.upper_threshold;
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
  int& mode = k4n_struct->matching.hough.cv_mode;
  int& ratio = k4n_struct->matching.hough.ratio;
  int& min_dist = k4n_struct->matching.hough.min_dist;
  int& min_radius = k4n_struct->matching.hough.min_radius;
  int& max_radius = k4n_struct->matching.hough.max_radius;
  float& param_1 = k4n_struct->matching.hough.param_1;
  float& param_2 = k4n_struct->matching.hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  for(int i=0; i<circles.size(); i++){
    k4n::structure::Circle circle;
    circle.center = glm::ivec2(circles[i][0], circles[i][1]);
    circle.radius = circles[i][2];
    vec_circle.push_back(circle);
  }

  //---------------------------
}
void Hough::find_mode_parameter(int mode){
  //---------------------------

  switch(mode){
    case k4n::hough::GRADIENT:{
      k4n_struct->matching.hough.param_1 = 100; //higher threshold for the Canny edge detector
      k4n_struct->matching.hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      k4n_struct->matching.hough.cv_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case k4n::hough::GRADIENT_ALT:{
      k4n_struct->matching.hough.param_1 = 300;
      k4n_struct->matching.hough.param_2 = 0.9;
      k4n_struct->matching.hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
      break;
    }
  }

  //---------------------------
}


}
