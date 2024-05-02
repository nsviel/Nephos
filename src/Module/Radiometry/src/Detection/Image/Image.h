#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::structure{class Circle;}
namespace k4n::dev{class Sensor;}


namespace rad::matching{

class Image
{
public:
  Image(rad::Node* node_radio);
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
  void draw_circle(cv::Mat& image, vector<rad::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image, k4n::dev::Sensor* sensor);

private:
  rad::Structure* radio_struct;
};

}
