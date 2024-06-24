#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::calibration{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Image;}
namespace utl::media{class Image;}


namespace rad::calibration{

class Rectangle
{
public:
  Rectangle(rad::calibration::Node* node_detection);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& image, utl::media::Image* output);

  //Subfunction
  void compute_rectangle_detection(cv::Mat& image, utl::media::Image* output);
  void draw_detected_rectangle(cv::Mat& image);
  bool is_rectangle(const vector<cv::Point>& contour);

private:
  rad::calibration::Structure* rad_struct;
  rad::calibration::Image* rad_image;
};

}
