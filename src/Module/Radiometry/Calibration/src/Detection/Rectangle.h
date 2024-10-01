#pragma once

#include <opencv2/opencv.hpp>

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Image;}
namespace utl::base{class Image;}


namespace rad::cal{

class Rectangle
{
public:
  Rectangle(rad::cal::Node* node_detection);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& image, std::shared_ptr<utl::base::Image> output);

  //Subfunction
  void compute_rectangle_detection(cv::Mat& image, std::shared_ptr<utl::base::Image> output);
  void draw_detected_rectangle(cv::Mat& image);
  bool is_rectangle(const std::vector<cv::Point>& contour);

private:
  rad::cal::Structure* rad_struct;
  rad::cal::Image* rad_image;
};

}
