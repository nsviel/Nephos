#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::image{class Image;}


namespace rad::detection::chart{

class Rectangle
{
public:
  Rectangle(rad::detection::Node* node_detection);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& image);

  //Subfunction
  void compute_rectangle_detection(cv::Mat& image);
  void draw_detected_rectangle(cv::Mat& image);
  bool is_rectangle(const vector<cv::Point>& contour);

private:
  rad::detection::Structure* rad_struct;
  rad::detection::image::Image* rad_image;
};

}
