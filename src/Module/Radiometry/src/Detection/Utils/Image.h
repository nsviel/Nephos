#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::structure{class Circle;}
namespace dat::base{class Sensor;}


namespace rad::detection::utils{

class Image
{
public:
  Image(rad::Node* node_radio);
  ~Image();

public:
  //Main function
  void draw_all_sphere(dat::base::Sensor* sensor);
  void draw_best_sphere(dat::base::Sensor* sensor);

  //Subfunction
  void convert_into_cv_image(utl::media::Image* input, cv::Mat& output);
  void convert_into_rgba(cv::Mat& input, cv::Mat& output);
  void convert_into_subimage(cv::Mat& image, dat::base::Sensor* sensor);
  void convert_into_utl_image(cv::Mat& input, utl::media::Image* output);
  void draw_circle(cv::Mat& image, vector<rad::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image, dat::base::Sensor* sensor);

private:
  rad::Structure* rad_struct;
};

}
