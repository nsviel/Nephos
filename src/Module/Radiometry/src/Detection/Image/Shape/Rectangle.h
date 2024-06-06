#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::image{class Image;}


namespace rad::detection::image{

class Rectangle
{
public:
  Rectangle(rad::Node* node_radio);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& image);

  //Subfunction
  void compute_rectangle_detection(cv::Mat& image);
  bool is_rectangle(const vector<cv::Point>& contour);

private:
  rad::Structure* rad_struct;
  rad::detection::image::Image* rad_image;
};

}
