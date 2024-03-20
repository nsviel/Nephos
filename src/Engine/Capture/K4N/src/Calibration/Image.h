#pragma once

#include <Utility/Specific/common.h>
#include <opencv2/opencv.hpp>

namespace k4n::dev{class Sensor;}


namespace k4n::hough{

enum Drawing{
  ALL = 0,
  BEST = 1,
};

}

namespace k4n::calibration{

class Image
{
public:
  Image();
  ~Image();

public:
  //Main function
  void draw_all_sphere(k4n::dev::Sensor* sensor);
  void draw_best_sphere(k4n::dev::Sensor* sensor);

  //Subfunction
  void convert_into_cv_image(utl::media::Image* input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_subimage(cv::Mat& image, k4n::dev::Sensor* sensor);
  void convert_into_utl_image(cv::Mat& input, utl::media::Image* output);
  void draw_circle(cv::Mat& image, vector<vec3>& vec_circle);
  void draw_boundingbox(cv::Mat& image, k4n::dev::Sensor* sensor);

private:

};

}
