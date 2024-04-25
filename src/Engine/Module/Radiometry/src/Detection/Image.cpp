#include "Image.h"

#include <K4N/Namespace.h>
#include <Radiometry/Namespace.h>

namespace k4n::matching{

//Constructor / Destructor
Image::Image(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::draw_all_sphere(k4n::dev::Sensor* sensor){
  if(sensor->detection.cv_image.empty()) return;
  //------------------------

  cv::Mat result;
  this->convert_into_rgba(sensor->detection.cv_image, result);
  this->draw_circle(result, sensor->detection.vec_circle);
  this->draw_bounding_box(result, sensor);
  this->convert_into_subimage(result, sensor);
  this->convert_into_utl_image(result, &sensor->image.hough);

  //------------------------
}
void Image::draw_best_sphere(k4n::dev::Sensor* sensor){
  if(sensor->detection.cv_image.empty()) return;
  //------------------------

  vector<k4n::structure::Circle> vec_circle;
  if(sensor->detection.vec_circle.size() > 0){
    vec_circle.push_back(sensor->detection.vec_circle[0]);
  }

  cv::Mat result;
  this->convert_into_rgba(sensor->detection.cv_image, result);
  this->draw_circle(result, vec_circle);
  this->draw_bounding_box(result, sensor);
  this->convert_into_subimage(result, sensor);
  this->convert_into_utl_image(result, &sensor->image.hough);

  //------------------------
}

//Subfunction
void Image::convert_into_cv_image(utl::media::Image* input, cv::Mat& output){
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
void Image::convert_into_subimage(cv::Mat& image, k4n::dev::Sensor* sensor){
  //------------------------

  cv::Point& center = sensor->detection.cv_center;
  float radius = (float)sensor->detection.cv_radius * k4n_struct->matching.bbox.scale;

  // Calculate the top-left corner coordinates of the bounding box
  int x = center.x - radius;
  int y = center.y - radius;

  //Check if coordinate are within image bounds
  if(x >= 0 && y >= 0 && x + radius*2 <= image.cols && y + radius*2 <= image.rows){
    // Create a Rect object representing the bounding box
    cv::Rect bounding_box(x, y, radius * 2, radius * 2);

    // Extract the subimage from the original image using the bounding box
    sensor->detection.cv_subimage = image(bounding_box).clone();
  }

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
void Image::draw_circle(cv::Mat& image, vector<k4n::structure::Circle>& vec_circle){
  if(vec_circle.size() == 0) return;
  //------------------------

  for(size_t i=0; i<vec_circle.size(); i++){
    k4n::structure::Circle& circle = vec_circle[i];
    cv::Point center(cvRound(circle.center.x), cvRound(circle.center.y));
    int radius = cvRound(circle.radius);

    // Draw the circle center
    cv::circle(image, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(image, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }

  //------------------------
}
void Image::draw_bounding_box(cv::Mat& image, k4n::dev::Sensor* sensor){
  //------------------------

  vector<k4n::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  if(vec_circle.size() == 0) return;

  k4n::structure::Circle& circle = vec_circle[0];
  sensor->detection.cv_center = cv::Point(cvRound(circle.center.x), cvRound(circle.center.y));
  sensor->detection.cv_radius = cvRound(circle.radius);

  cv::Point& center = sensor->detection.cv_center;
  float radius = (float)sensor->detection.cv_radius * k4n_struct->matching.bbox.scale;

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
