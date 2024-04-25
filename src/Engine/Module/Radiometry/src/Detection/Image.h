#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::structure{class Circle;}
namespace k4n::dev{class Sensor;}


namespace k4n::matching{

class Image
{
public:
  Image(k4n::Node* node_k4n);
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
  void draw_circle(cv::Mat& image, vector<k4n::structure::Circle>& vec_circle);
  void draw_bounding_box(cv::Mat& image, k4n::dev::Sensor* sensor);

private:
  k4n::structure::K4N* k4n_struct;
};

}
