#include "Rectangle.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::image{

//Constructor / Destructor
Rectangle::Rectangle(rad::Node* node_radio){
  //---------------------------

  rad::detection::Node* node_detection = node_radio->get_node_detection();

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::detection::image::Image(node_radio);

  //---------------------------
}
Rectangle::~Rectangle(){}

//Main function
void Rectangle::detect_rectangle(cv::Mat& image){
  if(image.empty()) return;
  //------------------------

  this->compute_rectangle_detection(image);
  this->draw_detected_rectangle(image);

  //------------------------
}

//Subfunction
void Rectangle::compute_rectangle_detection(cv::Mat& image){
  //---------------------------

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);

  // Find contours
  vector<vector<cv::Point>> contours;
  cv::findContours(image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  // Draw rectangles
  for(int i=0; i<contours.size(); i++){
    if(is_rectangle(contours[i])){
      // Calculate the BB and center of the rectangle
      cv::Rect boundingBox = cv::boundingRect(contours[i]);
      cv::Point center(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);

      // Draw rectangles
      cv::circle(result, center, 1, cv::Scalar(0, 0, 255, 255), 1, cv::LINE_AA);
      cv::drawContours(result, contours, i, cv::Scalar(0, 255, 0, 255), 2, cv::LINE_AA);
      cv::rectangle(result, boundingBox, cv::Scalar(255, 150, 0, 255), 1, cv::LINE_AA);
    }
  }

  rad_image->convert_into_subimage(result);
  rad_image->convert_into_utl_image(result, &rad_struct->sphere.image);

  //---------------------------
}
void Rectangle::draw_detected_rectangle(cv::Mat& image){
  //---------------------------



  //---------------------------
}
bool Rectangle::is_rectangle(const vector<cv::Point>& contour){
  const double minAspectRatio = 0.7;
  const double maxAspectRatio = 3;
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
