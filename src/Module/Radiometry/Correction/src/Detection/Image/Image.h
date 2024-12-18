#pragma once

#include <opencv2/opencv.hpp>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor::structure{class Circle;}
namespace dat::base{class Sensor;}
namespace utl::base{class Image;}


namespace rad::cor::image{

class Image
{
public:
  Image(rad::cor::Node* node_correction);
  ~Image();

public:
  //Main function
  void apply_canny(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void convert_into_gray(cv::Mat& input, cv::Mat& output);
  void convert_into_cv_image(std::shared_ptr<utl::base::Image> input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_utl_image(cv::Mat& input, std::shared_ptr<utl::base::Image> output);

  //Shape function
  void draw_circle(cv::Mat& image, std::vector<rad::cor::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image);

private:
  rad::cor::Structure* rad_struct;
};

}
