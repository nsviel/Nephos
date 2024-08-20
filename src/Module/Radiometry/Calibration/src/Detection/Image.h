#pragma once

#include <opencv2/opencv.hpp>

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal::structure{class Circle;}
namespace dyn::prc::base{class Sensor;}
namespace utl::media{class Image;}


namespace rad::cal{

class Image
{
public:
  Image(rad::cal::Node* node_correction);
  ~Image();

public:
  //Main function
  void apply_canny(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void convert_into_gray(cv::Mat& input, cv::Mat& output);
  void convert_into_cv_image(utl::media::Image* input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_utl_image(cv::Mat& input, utl::media::Image* output);

private:
  rad::cal::Structure* rad_struct;
};

}
