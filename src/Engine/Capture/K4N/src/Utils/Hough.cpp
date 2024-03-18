#include "Hough.h"


namespace k4n::utils{

//Constructor / Destructor
Hough::Hough(){
  //---------------------------


  //---------------------------
}
Hough::~Hough(){}

//Main function
void Hough::sphere_detection(utl::media::Image* image, utl::media::Image* result){
  if(image == nullptr) return;
  if(image->data.size() == 0) return;
  //------------------------

  // Create an Hough Mat object from the image data
  cv::Mat raw_image(image->height, image->width, CV_8UC4, image->data.data());

  //Pre processing
  cv::Mat pre_image;
  this->preprocessing(raw_image, pre_image);

  //Parameter
  this->min_dist = pre_image.rows / 8;
  this->find_mode_parameter();

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  cv::HoughCircles(pre_image, vec_circle, hough_mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  //Final step
  //this->draw_result(pre_image, vec_circle);
  this->convert_to_utl_image(pre_image, vec_circle, result);

  //------------------------
}

//Subfunction
void Hough::find_mode_parameter(){
  //---------------------------

  switch(mode){
    case k4n::hough::GRADIENT:{
      this->param_1 = 100; //higher threshold for the Canny edge detector
      this->param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      this->hough_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case k4n::hough::GRADIENT_ALT:{
      this->param_1 = 300;
      this->param_2 = 0.9;
      this->hough_mode = cv::HOUGH_GRADIENT_ALT;
      break;
    }
  }

  //---------------------------
}
void Hough::find_sphere_data(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle){
  //---------------------------

  // Ensure at least one circle is detected
  if (vec_circle.size() > 0) {
    // Retrieve the parameters of the detected circle
    float center_x = vec_circle[0][0];
    float center_y = vec_circle[0][1];
    float radius = vec_circle[0][2];

    // Iterate over the bounding box of the circle
    for (int y = center_y - radius; y <= center_y + radius; y++) {
      for (int x = center_x - radius; x <= center_x + radius; x++) {
        // Calculate the distance from the center of the circle
        float distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));

        // Check if the pixel lies within the circle
        if (distance <= radius) {
          // Retrieve the pixel value at (x, y)
          cv::Scalar pixel_value = image.at<uchar>(y, x);
          // Do something with the pixel value
          // For example, print the pixel value
          std::cout << "Pixel value at (" << x << ", " << y << "): " << pixel_value << std::endl;
        }
      }
    }
  }

  //---------------------------
}
void Hough::preprocessing(cv::Mat& input, cv::Mat& output){
  //---------------------------

  if(apply_canny){
    // Perform canny edge detection
    cv::Canny(input, output, canny_thres_lower, canny_thres_upper);
  }else{
    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);
  }

  //---------------------------
}
void Hough::draw_result(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle){
  //---------------------------

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(image, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(44, 250, 44), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(44, 44, 250), 1, cv::LINE_AA);
  }

  // Display the result
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //---------------------------
}
void Hough::convert_to_utl_image(cv::Mat& image_raw, std::vector<cv::Vec3f>& vec_circle, utl::media::Image* image){
  //------------------------

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(image_raw, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(44, 255, 44, 255), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(44, 44, 255, 255), 1, cv::LINE_AA);
  }

  // Set the dimensions of the utl::media::Image
  image->width = result.cols;
  image->height = result.rows;
  image->channel_nb = result.channels(); // Assuming result is in BGRA format
  image->format = "B8G8R8A8_SRGB";
  image->new_data = true;

  // Calculate the size of the pixel data
  size_t data_size = result.cols * result.rows * result.channels();
  image->data.resize(data_size);
  image->size = data_size;

  // Copy the pixel data from the OpenCV image to the utl::media::Image
  std::memcpy(image->data.data(), result.data, data_size);

  //------------------------
}




}
