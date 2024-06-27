#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction::structure{class Circle;}
namespace dyn::base{class Sensor;}


namespace rad::correction::image{

class Image
{
public:
  Image(rad::correction::Node* node_correction);
  ~Image();

public:
  //Main function
  void apply_canny(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void convert_into_gray(cv::Mat& input, cv::Mat& output);
  void convert_into_cv_image(utl::media::Image* input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_utl_image(cv::Mat& input, utl::media::Image* output);

  //Shape function
  void draw_circle(cv::Mat& image, std::vector<rad::correction::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image);

private:
  rad::correction::Structure* rad_struct;
};

}
