#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace rad::detection::image{class Image;}


namespace rad::detection::image{

class Circle
{
public:
  Circle(rad::Node* node_radio);
  ~Circle();

public:
  //Main function
  void detect_circle(cv::Mat& image);

  //Hough function
  void compute_hough_circle(cv::Mat& image);
  void find_hough_parameter(int mode);

  //Draw function
  void draw_detected_circle(cv::Mat& image);
  void draw_all_circle(cv::Mat& image);
  void draw_best_circle(cv::Mat& image);

private:
  rad::detection::Structure* rad_struct;
  rad::detection::image::Image* rad_image;
};

}
