#include "Hough.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Hough::Hough(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  this->find_mode_parameter(k4n::hough::ALL);

  //---------------------------
}
Hough::~Hough(){}

//Main function
vector<vec3> Hough::sphere_detection(cv::Mat& input, cv::Mat& output){
  if(input.empty()) return vector<vec3>();
  //------------------------

  //Pre processing
  this->preprocessing(input, output);

  // Perform Hough Transform to detect lines
  vector<vec3> vec_circle = compute_hough_circle(output);

  //------------------------
  return vec_circle;
}

//Algo function
void Hough::preprocessing(cv::Mat& input, cv::Mat& output){
  //---------------------------

  if(k4n_struct->hough.apply_canny){
    // Perform canny edge detection
    int& thresh_lower = k4n_struct->hough.canny_thres_lower;
    int& thresh_upper = k4n_struct->hough.canny_thres_upper;
    cv::Canny(input, output, thresh_lower, thresh_upper);
  }else{
    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(input, output, cv::COLOR_RGBA2GRAY);
  }

  //---------------------------
}
vector<vec3> Hough::compute_hough_circle(cv::Mat& image){
  //---------------------------

  std::vector<cv::Vec3f> circles;
  int& mode = k4n_struct->hough.cv_mode;
  int& ratio = k4n_struct->hough.ratio;
  int& min_dist = k4n_struct->hough.min_dist;
  int& min_radius = k4n_struct->hough.min_radius;
  int& max_radius = k4n_struct->hough.max_radius;
  float& param_1 = k4n_struct->hough.param_1;
  float& param_2 = k4n_struct->hough.param_2;

  cv::HoughCircles(image, circles, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);
   k4n_struct->hough.nb_detection = circles.size();

  vector<vec3> vec_circle;
  for(int i=0; i<circles.size(); i++){
    vec_circle.push_back(vec3(circles[i][0], circles[i][1], circles[i][2]));
  }

  //---------------------------
  return vec_circle;
}

//Subfunction
void Hough::find_mode_parameter(int mode){
  //---------------------------

  switch(mode){
    case k4n::hough::GRADIENT:{
      k4n_struct->hough.param_1 = 100; //higher threshold for the Canny edge detector
      k4n_struct->hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      k4n_struct->hough.cv_mode = cv::HOUGH_GRADIENT;
      break;
    }
    case k4n::hough::GRADIENT_ALT:{
      k4n_struct->hough.param_1 = 300;
      k4n_struct->hough.param_2 = 0.9;
      k4n_struct->hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
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

}
