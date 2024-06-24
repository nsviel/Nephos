#include "Rectangle.h"

#include <Radiometry/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Rectangle::Rectangle(rad::calibration::Node* node_detection){
  //---------------------------

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::calibration::Image(node_detection);

  //---------------------------
}
Rectangle::~Rectangle(){}

//Main function
void Rectangle::detect_rectangle(cv::Mat& image, utl::media::Image* output){
  if(image.empty()) return;
  //------------------------

  this->compute_rectangle_detection(image, output);
  this->draw_detected_rectangle(image);

  //------------------------
}

//Subfunction
void Rectangle::compute_rectangle_detection(cv::Mat& image, utl::media::Image* output){
  //---------------------------

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);

  // Find contours
  vector<vector<cv::Point>> contours;
  cv::findContours(image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  double bestScore = std::numeric_limits<double>::max(); // Initialize to a large value
  cv::Rect bestBoundingBox;
  cv::Point bestCenter;

  // Iterate through the contours to find the most squared rectangle
  for (int i = 0; i < contours.size(); i++) {
      if (is_rectangle(contours[i])) {
          // Calculate the bounding box and center of the rectangle
          cv::Rect boundingBox = cv::boundingRect(contours[i]);
          float aspectRatio = static_cast<float>(boundingBox.width) / boundingBox.height;
          double score = std::abs(aspectRatio - 1); // Score based on how close the aspect ratio is to 1

          if (score < bestScore) {
              bestScore = score;
              bestBoundingBox = boundingBox;
              bestCenter = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
          }
      }
  }

  // Draw the most squared rectangle
  if (bestScore < std::numeric_limits<double>::max()) {
      cv::circle(result, bestCenter, 1, cv::Scalar(0, 0, 255, 255), 1, cv::LINE_AA);
      cv::rectangle(result, bestBoundingBox, cv::Scalar(255, 150, 0, 255), 1, cv::LINE_AA);
  }

  rad_image->convert_into_utl_image(result, output);

  //---------------------------
}
void Rectangle::draw_detected_rectangle(cv::Mat& image){
  //---------------------------



  //---------------------------
}
bool Rectangle::is_rectangle(const vector<cv::Point>& contour){
  const double minAspectRatio = 0.95;
  const double maxAspectRatio = 1.05;
  //---------------------------

  // Approximate the contour to a polygon
  vector<cv::Point> approx;
  cv::approxPolyDP(contour, approx, cv::arcLength(contour, true) * 0.02, true);

  // Check if the polygon has 4 vertices and is convex
  if(cv::isContourConvex(approx)){
    // Calculate the bounding box of the polygon
    cv::Rect boundingBox = cv::boundingRect(approx);
    double aspectRatio = (double)boundingBox.width / boundingBox.height;

    // Check the aspect ratio to confirm it's approximately a rectangle
    if(aspectRatio >= minAspectRatio && aspectRatio <= maxAspectRatio){
      return true;
    }
  }

  //---------------------------
  return false;
}


}
