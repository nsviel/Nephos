#include "Image.h"


namespace k4n::calibration{

//Constructor / Destructor
Image::Image(){
  //---------------------------


  //---------------------------
}
Image::~Image(){}

//Main function
void Image::draw_all_sphere(utl::media::Image* input, vector<vec3>& vec_circle, utl::media::Image* output){
/*  if(input == nullptr) return;
  if(input->data.size() == 0) return;
  //------------------------

  // Create an Image Mat object from the image data
  cv::Mat image_raw(input->height, input->width, CV_8UC4, input->data.data());

  //Pre processing
  cv::Mat pre_image;
  this->preprocessing(image_raw, pre_image);

  //Convert to RGBA
  cv::Mat result;
  cv::cvtColor(pre_image, result, cv::COLOR_RGBA2BGRA);

  // Draw the detected vec_circle on the original image
  cv::cvtColor(pre_image, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }


  // Draw marker on the result image
  cv::Point center(250, 160); // Coordinates of the marker center
  cv::Scalar color(0, 0, 0); // Marker color in BGR format
  int thickness = 10; // Thickness of the marker
  int markerType = cv::MARKER_CROSS; // Marker type
  int markerSize = 100; // Marker size
  int lineType = cv::LINE_AA; // Line type

  // Draw marker on the result image
  int width = 100; // Width of the rectangle
  int height = 50; // Height of the rectangle

  // Calculate the coordinates of the top-left corner of the rectangle
  cv::Point tl(center.x - width / 2, center.y - height / 2);

  // Calculate the coordinates of the bottom-right corner of the rectangle
  cv::Point br(center.x + width / 2, center.y + height / 2);

  // Draw the rectangle on the result image
  cv::rectangle(result, tl, br, color, thickness, lineType);

  cv::drawMarker(result, center, color, markerType, markerSize, thickness, lineType);


  // Set the dimensions of the utl::media::Image
  output->width = result.cols;
  output->height = result.rows;
  output->channel_nb = result.channels(); // Assuming result is in BGRA format
  output->format = "B8G8R8A8_SRGB";
  output->new_data = true;

  // Calculate the size of the pixel data
  size_t data_size = result.cols * result.rows * result.channels();
  output->data.resize(data_size);
  output->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::media::Image
  std::memcpy(output->data.data(), result.data, data_size);
*/
  //------------------------
}
void Image::draw_best_sphere(utl::media::Image* input, vector<vec3>& vec_circle, utl::media::Image* output){
  /*if(input == nullptr) return;
  if(input->data.size() == 0) return;
  //------------------------

  // Create an Image Mat object from the image data
  cv::Mat image_raw(input->height, input->width, CV_8UC4, input->data.data());

  //Pre processing
  cv::Mat pre_image;
  this->preprocessing(image_raw, pre_image);

  //Convert to RGBA
  cv::Mat result;
  cv::cvtColor(pre_image, result, cv::COLOR_RGBA2BGRA);

  //Draw circle
  if(vec_circle.size() > 0){
    vec3 circle = vec_circle[0];

    cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
    int radius = cvRound(circle[2]);
    cv::circle(result, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);
    cv::circle(result, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }

  // Set the dimensions of the utl::media::Image
  output->width = result.cols;
  output->height = result.rows;
  output->channel_nb = result.channels(); // Assuming result is in BGRA format
  output->format = "B8G8R8A8_SRGB";
  output->new_data = true;

  // Calculate the size of the pixel data
  size_t data_size = result.cols * result.rows * result.channels();
  output->data.resize(data_size);
  output->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::media::Image
  std::memcpy(output->data.data(), result.data, data_size);
*/
  //------------------------
}




}
