#include "Canny.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Canny::Canny(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Canny::~Canny(){}

//Main function
void Canny::apply_canny(cv::Mat& input, cv::Mat& output){
  if(input.empty()) return;
  //------------------------

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

  //------------------------
}

}
