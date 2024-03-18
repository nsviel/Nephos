#pragma once

#include <Utility/Specific/common.h>
#include <opencv2/opencv.hpp>


namespace k4n::hough{

enum Mode{
  GRADIENT = 0,
  STANDARD = 1,
  PROBABILISTIC = 2,
};

}

namespace k4n::utils{

class Hough
{
public:
  Hough();
  ~Hough();

public:
  //Main function
  void sphere_detection(utl::media::Image* image, utl::media::Image* result);

  //Subfunction
  void find_mode_parameter();
  void find_sphere_data(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle);
  void preprocessing(cv::Mat& input, cv::Mat& output);
  void draw_result(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle);
  void convert_to_utl_image(cv::Mat& image_raw, std::vector<cv::Vec3f>& vec_circle, utl::media::Image* image);

  inline int* get_mode(){return &mode;}
  inline int* get_ratio(){return &ratio;}
  inline int* get_min_dist(){return &min_dist;}
  inline int* get_min_radius(){return &min_radius;}
  inline int* get_max_radius(){return &max_radius;}
  inline int* get_canny_thres_lower(){return &canny_thres_lower;}
  inline int* get_canny_thres_upper(){return &canny_thres_upper;}
  inline float* get_param_1(){return &param_1;}
  inline float* get_param_2(){return &param_2;}
  inline bool* get_apply_canny(){return &apply_canny;}

private:
  int mode = k4n::hough::GRADIENT;
  int hough_mode = cv::HOUGH_GRADIENT;
  int ratio = 1;
  int min_dist = 0;
  int min_radius = 5;
  int max_radius = 50;
  int canny_thres_lower = 50;
  int canny_thres_upper = 150;
  float param_1 = 0;
  float param_2 = 0;
  bool apply_canny = false;
};

}
