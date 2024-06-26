#include "Rectangle.h"

#include <Radiometry/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Rectangle::Rectangle(rad::calibration::Node* node_detection){
  //---------------------------

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::calibration::Image(node_detection);

  rad_struct->hough.param_1 = 300;
  rad_struct->hough.param_2 = 0.9;
  rad_struct->hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
  
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



bool lines_intersect(cv::Vec2f line1, cv::Vec2f line2, cv::Point2f& intersection){
    float rho1 = line1[0], theta1 = line1[1];
    float rho2 = line2[0], theta2 = line2[1];
    float A1 = cos(theta1), B1 = sin(theta1);
    float A2 = cos(theta2), B2 = sin(theta2);
    float det = A1 * B2 - A2 * B1;
    if(std::abs(det) < 1e-2) return false;
    intersection.x = (rho2 * B1 - rho1 * B2) / det;
    intersection.y = (rho1 * A2 - rho2 * A1) / det;
    return true;
}

//Subfunction
void Rectangle::compute_rectangle_detection(cv::Mat& image, utl::media::Image* output){
  //---------------------------

  cv::Mat result;
  rad_image->convert_into_rgba(image, result);

  // Detect circles using Hough Circle Transform
  std::vector<cv::Vec3f> circles;
  int& mode = rad_struct->hough.cv_mode;
  int& ratio = rad_struct->hough.ratio;
  int& min_dist = rad_struct->hough.min_dist;
  int& min_radius = rad_struct->hough.min_radius;
  int& max_radius = rad_struct->hough.max_radius;
  float& param_1 = rad_struct->hough.param_1;
  float& param_2 = rad_struct->hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

   // Draw detected circles
   for(size_t i = 0; i < circles.size(); i++){
       cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
       int radius = cvRound(circles[i][2]);

       // Draw the circle center
       cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);

       // Draw the circle outline
       cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
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
