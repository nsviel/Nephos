#include "Rectangle.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Rectangle::Rectangle(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_radio);

  //---------------------------
}
Rectangle::~Rectangle(){}

//Main function
void Rectangle::detect_rectangle(cv::Mat& image){
  if(image.empty()) return;
  //------------------------

  cv::Mat gray, canny;
  rad_image->convert_into_gray(image, gray);
  rad_image->apply_canny(gray, canny);
  this->truc(canny);

  //------------------------
}

void Rectangle::truc(cv::Mat& image){
  //---------------------------

  // Find contours
  vector<vector<cv::Point>> contours;
  cv::findContours(image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  // Draw rectangles
  for(size_t i = 0; i < contours.size(); i++){
    if(is_rectangle(contours[i])){
      cv::drawContours(image, contours, (int)i, cv::Scalar(0, 255, 0), 2);
    }
  }

  // Display the result
  cv::namedWindow("Detected Rectangles", cv::WINDOW_AUTOSIZE);
  cv::imshow("Detected Rectangles", image);

  cv::waitKey(0);

  //---------------------------
}

//Subfunction
bool is_rectangle(const vector<cv::Point>& contour){
  const double minAspectRatio = 0.8;
  const double maxAspectRatio = 1.2;
  //---------------------------

  // Approximate the contour to a polygon
  vector<cv::Point> approx;
  cv::approxPolyDP(contour, approx, cv::arcLength(contour, true) * 0.02, true);

  // Check if the polygon has 4 vertices and is convex
  if(approx.size() == 4 && cv::isContourConvex(approx)) {
    // Calculate the bounding box of the polygon
    cv::Rect boundingBox = cv::boundingRect(approx);
    double aspectRatio = (double)boundingBox.width / boundingBox.height;

    // Check the aspect ratio to confirm it's approximately a rectangle
    if (aspectRatio >= minAspectRatio && aspectRatio <= maxAspectRatio) {
      return true;
    }
  }

  //---------------------------
  return false;
}

}
