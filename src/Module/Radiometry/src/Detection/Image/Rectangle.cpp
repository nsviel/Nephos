#include "Rectangle.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Rectangle::Rectangle(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Rectangle::~Rectangle(){}

//Main function
void Rectangle::truc(){
  //---------------------------

  // Read the image
  cv::Mat image = cv::imread("path_to_image.jpg");

  // Convert to grayscale
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  // Apply a binary threshold to the grayscale image
  cv::Mat binary;
  cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY);

  // Find contours
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  // Iterate through each contour and detect rectangles
  for (size_t i = 0; i < contours.size(); i++) {
      // Approximate the contour to a polygon
      std::vector<cv::Point> polygon;
      cv::approxPolyDP(contours[i], polygon, cv::arcLength(contours[i], true) * 0.02, true);

      // Check if the approximated polygon has 4 vertices (is a rectangle)
      if (polygon.size() == 4) {
          // Draw the rectangle on the original image
          cv::drawContours(image, std::vector<std::vector<cv::Point>>{polygon}, -1, cv::Scalar(0, 255, 0), 3);
      }
  }

  // Show the result
  cv::imshow("Rectangles Detected", image);
  cv::waitKey(0);

  //---------------------------
}

}
