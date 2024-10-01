#pragma once

#include <opencv2/opencv.hpp>

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal::structure{class Circle;}
namespace dat::base{class Sensor;}
namespace utl::base{class Image;}


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
  void convert_into_cv_image(std::shared_ptr<utl::base::Image> input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_utl_image(cv::Mat& input, std::shared_ptr<utl::base::Image> output);

private:
  rad::cal::Structure* rad_struct;
};

}
