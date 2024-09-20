#include "Image.h"

#include <Radiometry/Correction/Namespace.h>


namespace rad::cor::image{

//Constructor / Destructor
Image::Image(rad::cor::Node* node_correction){
  //---------------------------

  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::apply_canny(cv::Mat& input, cv::Mat& output){
  if(rad_struct->canny.apply == false){
    output = input;
    return;
  }
  //---------------------------

  // Perform canny edge detection
  int& thresh_lower = rad_struct->canny.thres_lower;
  int& thresh_upper = rad_struct->canny.thres_upper;
  cv::Canny(input, output, thresh_lower, thresh_upper);

  //---------------------------
}

//Conversion function
void Image::convert_into_gray(cv::Mat& input, cv::Mat& output){
  //---------------------------

  // Convert the image to grayscale
  cv::Mat gray_image;
  cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);

  //---------------------------
}
void Image::convert_into_cv_image(std::shared_ptr<utl::media::Image> input, cv::Mat& output){
  //------------------------

  output.release();
  if(input == nullptr) return;
  if(input->data.size() == 0) return;

  output = cv::Mat(input->height, input->width, CV_8UC4, input->data.data());

  //------------------------
}
void Image::convert_into_rgba(cv::Mat& input, cv::Mat& output){
  //------------------------

  // Convert edges to BGR for drawing
  cv::cvtColor(input, output, cv::COLOR_RGBA2BGRA);

  //------------------------
}
void Image::convert_into_utl_image(cv::Mat& input, std::shared_ptr<utl::media::Image> output){
  //------------------------

  // Set the dimensions of the utl::media::Image
  output->width = input.cols;
  output->height = input.rows;
  output->channel_nb = input.channels(); // Assuming result is in BGRA format
  output->format = "BGRA8";

  // Calculate the size of the pixel data
  size_t data_size = input.cols * input.rows * input.channels();
  output->data.resize(data_size);
  output->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::media::Image
  std::memcpy(output->data.data(), input.data, data_size);

  //------------------------
}

//Shape function
void Image::draw_circle(cv::Mat& image, std::vector<rad::cor::structure::Circle>& vec_circle){
  if(vec_circle.size() == 0) return;
  //------------------------

  for(size_t i=0; i<vec_circle.size(); i++){
    rad::cor::structure::Circle& circle = vec_circle[i];
    cv::Point center(cvRound(circle.center.x), cvRound(circle.center.y));
    int radius = cvRound(circle.radius);

    // Draw the circle center
    cv::circle(image, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(image, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }

  //------------------------
}
void Image::draw_bounding_box(cv::Mat& image){
  //------------------------

  std::vector<rad::cor::structure::Circle>& vec_circle = rad_struct->hough.vec_circle;
  if(vec_circle.size() == 0) return;

  rad::cor::structure::Circle& circle = vec_circle[0];
  cv::Point center = cv::Point(cvRound(circle.center.x), cvRound(circle.center.y));
  float radius = cvRound(circle.radius) * rad_struct->bbox.scale;

  //Draw cross marker
  int markerSize = 10; // Marker size
  cv::drawMarker(image, center, cv::Scalar(44, 150, 255, 255), cv::MARKER_CROSS, markerSize, 2, cv::LINE_AA);

  //Draw rectangle marker
  cv::Point tl(center.x - radius, center.y - radius);
  cv::Point br(center.x + radius, center.y + radius);
  cv::rectangle(image, tl, br, cv::Scalar(255, 150, 44, 255), 2, cv::LINE_AA);

  //------------------------
}

}
