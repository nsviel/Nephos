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
  void sphere_detection(utl::media::Image* image);

  //Subfunction
  void find_mode_parameter(float& param_1, float& param_2);
  void preprocessing(cv::Mat& input, cv::Mat& output);
  void draw_result(cv::Mat& image, std::vector<cv::Vec3f>& vec_circle);

  inline int* get_mode(){return &mode;}
  inline int* get_ratio(){return &ratio;}
  inline float* get_min_dist(){return &min_dist;}
  inline float* get_min_radius(){return &min_radius;}
  inline float* get_max_radius(){return &max_radius;}
  inline bool* get_apply_canny(){return &apply_canny;}

private:
  int mode = k4n::hough::GRADIENT;
  int ratio = 1;
  float min_dist = 0;
  float min_radius = 5;
  float max_radius = 50;
  bool apply_canny = false;
};

}
