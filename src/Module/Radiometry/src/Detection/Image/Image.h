#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace dat::base{class Sensor;}


namespace rad::detection::image{

class Image
{
public:
  Image(rad::Node* node_radio);
  ~Image();

public:
  //Main function
  void apply_canny(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void convert_into_gray(cv::Mat& input, cv::Mat& output);
  void convert_into_cv_image(utl::media::Image* input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_subimage(cv::Mat& image);
  void convert_into_utl_image(cv::Mat& input, utl::media::Image* output);

  //Shape function
  void draw_circle(cv::Mat& image, vector<rad::detection::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image);

private:
  rad::Structure* rad_struct;
};

}
