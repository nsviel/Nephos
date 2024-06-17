#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction::image{class Image;}
namespace utl::media{class Image;}


namespace rad::calibration{

class Rectangle
{
public:
  Rectangle(rad::correction::Node* node_detection);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& image, utl::media::Image* output);

  //Subfunction
  void compute_rectangle_detection(cv::Mat& image, utl::media::Image* output);
  void draw_detected_rectangle(cv::Mat& image);
  bool is_rectangle(const vector<cv::Point>& contour);

private:
  rad::correction::Structure* rad_struct;
  rad::correction::image::Image* rad_image;
};

}
