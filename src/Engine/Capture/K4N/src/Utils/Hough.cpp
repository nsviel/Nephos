#include "Hough.h"


namespace k4n::utils{

//Constructor / Destructor
Hough::Hough(){
  //---------------------------


  //---------------------------
}
Hough::~Hough(){}

//Main function
void Hough::sphere_detection(utl::media::Image* image){
  //------------------------

  // Create an Hough Mat object from the image data
  cv::Mat raw_image(image->height, image->width, CV_8UC4, image->data.data());

  //Pre processing
  cv::Mat pre_image;
  this->preprocessing(raw_image, pre_image);

  //Parameter
  this->min_dist = pre_image.rows / 8;
  float param_1, param_2;
  this->find_mode_parameter(param_1, param_2);

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  cv::HoughCircles(pre_image, vec_circle, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);
  this->draw_result(pre_image, vec_circle);

  //------------------------
}

//Subfunction
void Hough::find_mode_parameter(float& param_1, float& param_2){
  //---------------------------

  switch(mode){
    case cv::HOUGH_GRADIENT:{
      param_1 = 100; //higher threshold for the Canny edge detector
      param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      break;
    }
    case cv::HOUGH_STANDARD:{
      param_1 = 0; //not used
      param_2 = 30; //minimum number of intersections to "detect" a circle
      break;
    }
    case cv::HOUGH_PROBABILISTIC:{
      param_1 = 10; //minimum distance between the centers of the detected vec_circle
      param_2 = 30; //minimum radius of the vec_circle to detect
      break;
    }
  }

  //---------------------------
}
void Hough::preprocessing(cv::Mat& input, cv::Mat& output){
  //---------------------------

  if(apply_canny){
    // Perform canny edge detection
    cv::Canny(input, output, canny_thres_lower, canny_thres_upper);
  }else{
    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);
  }

  //---------------------------
}
void Hough::draw_result(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle){
  //---------------------------

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(image, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(44, 250, 44), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(44, 44, 250), 1, cv::LINE_AA);
  }

  // Display the result
  say(vec_circle.size());
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //---------------------------
}

}
