#include "Image.h"

#include <Radiometry/Calibration/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Image::Image(rad::cal::Node* node_correction){
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
void Image::convert_into_cv_image(std::shared_ptr<utl::base::Image> input, cv::Mat& output){
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
void Image::convert_into_utl_image(cv::Mat& input, std::shared_ptr<utl::base::Image> output){
  //------------------------

  // Set the dimensions of the utl::base::Image
  output->width = input.cols;
  output->height = input.rows;
  output->channel_nb = input.channels(); // Assuming result is in BGRA format
  output->format = "RGBA8";

  // Calculate the size of the pixel data
  size_t data_size = input.cols * input.rows * input.channels();
  output->data.resize(data_size);
  output->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::base::Image
  std::memcpy(output->data.data(), input.data, data_size);

  //------------------------
}

}
