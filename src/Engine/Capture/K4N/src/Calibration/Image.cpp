#include "Image.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Image::Image(){
  //---------------------------


  //---------------------------
}
Image::~Image(){}

//Main function
void Image::draw_all_sphere(k4n::dev::Sensor* sensor){
  if(sensor->calibration.cv_image.empty()) return;
  //------------------------

  cv::Mat result;
  this->convert_into_rgba(sensor->calibration.cv_image, result);
  this->draw_circle(result, sensor->calibration.vec_circle);
  this->draw_boundingbox(result, sensor);
  this->convert_into_utl_image(result, &sensor->image.hough);

  //------------------------
}
void Image::draw_best_sphere(k4n::dev::Sensor* sensor){
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

//Subfunction
void Image::convert_into_rgba(cv::Mat& input, cv::Mat& output){
  //------------------------

  // Convert edges to BGR for drawing
  cv::cvtColor(input, output, cv::COLOR_RGBA2BGRA);

  //------------------------
}
void Image::convert_into_utl_image(cv::Mat& input, utl::media::Image* output){
  //------------------------

  // Set the dimensions of the utl::media::Image
  output->width = input.cols;
  output->height = input.rows;
  output->channel_nb = input.channels(); // Assuming result is in BGRA format
  output->format = "B8G8R8A8_SRGB";
  output->new_data = true;

  // Calculate the size of the pixel data
  size_t data_size = input.cols * input.rows * input.channels();
  output->data.resize(data_size);
  output->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::media::Image
  std::memcpy(output->data.data(), input.data, data_size);

  //------------------------
}
void Image::draw_circle(cv::Mat& image, vector<vec3>& vec_circle){
  if(vec_circle.size() == 0) return;
  //------------------------

  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(image, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(image, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }

  //------------------------
}
void Image::draw_boundingbox(cv::Mat& image, k4n::dev::Sensor* sensor){
  //------------------------

  if(sensor->calibration.vec_circle.size() == 0) return;
  sensor->calibration.cv_center = cv::Point(cvRound(sensor->calibration.vec_circle[0][0]), cvRound(sensor->calibration.vec_circle[0][1]));
  sensor->calibration.cv_radius = cvRound(sensor->calibration.vec_circle[0][2]);

  cv::Point& center = sensor->calibration.cv_center;
  int& radius = sensor->calibration.cv_radius * sensor->calibration.cv_BB_scale;

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
