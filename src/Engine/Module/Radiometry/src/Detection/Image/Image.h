#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace radio{class Structure;}
namespace radio::structure{class Circle;}
namespace k4n::dev{class Sensor;}


namespace radio::matching{

class Image
{
public:
  Image(radio::Structure* radio_struct);
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
  void draw_circle(cv::Mat& image, vector<radio::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image, k4n::dev::Sensor* sensor);

private:
  radio::Structure* radio_struct;
};

}
