#include "Hough.h"

#include <opencv2/opencv.hpp>


namespace k4n::utils{

//Constructor / Destructor
Hough::Hough(){
  //---------------------------

  //---------------------------
}
Hough::~Hough(){}

//Sphere
void Hough::find_sphere_in_image(utl::media::Image* image){
  //------------------------

  // Create an Hough Mat object from the image data
  cv::Mat cv_image(image->height, image->width, CV_8UC4, image->data.data());

  // Convert the image to grayscale
  cv::Mat gray_image;
  cv::cvtColor(cv_image, gray_image, cv::COLOR_RGBA2GRAY);

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  int ratio = 1;
  float min_dist = gray_image.rows / 8;
  float min_radius = 5;
  float max_radius = 50;

  //modes:
  // - cv::HOUGH_GRADIENT
  // - cv::HOUGH_STANDARD
  // - cv::HOUGH_PROBABILISTIC
  int mode = cv::HOUGH_GRADIENT;

  float param_1, param_2;
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

  cv::HoughCircles(gray_image, vec_circle, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(gray_image, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
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
  cv::imshow("Raw Image", cv_image);
  cv::waitKey(0);
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //------------------------
}
void Hough::find_sphere_in_image_with_canny(utl::media::Image* image){
  //------------------------

  // Create an Hough Mat object from the image data
  cv::Mat cv_image(image->height, image->width, CV_8UC4, image->data.data());

  // Perform edge detection (you may need to adjust parameters for your specific image)
  cv::Mat edges;
  cv::Canny(cv_image, edges, 50, 150);

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  int ratio = 1;
  float min_dist = edges.rows / 8;
  float min_radius = 5;
  float max_radius = 50;

  //modes:
  // - cv::HOUGH_GRADIENT
  // - cv::HOUGH_STANDARD
  // - cv::HOUGH_PROBABILISTIC
  int mode = cv::HOUGH_GRADIENT;

  float param_1, param_2;
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

  cv::HoughCircles(edges, vec_circle, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(edges, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
  }

  // Display the result
  say(vec_circle.size());
  cv::imshow("Raw Image", cv_image);
  cv::waitKey(0);
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //------------------------
}

}
