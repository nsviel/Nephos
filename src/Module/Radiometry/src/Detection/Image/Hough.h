#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::structure{class Circle;}


namespace rad::detection{

class Hough
{
public:
  Hough(rad::Node* node_radio);
  ~Hough();

public:
  //Main function
  vector<rad::structure::Circle> sphere_detection(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void preprocessing(cv::Mat& input, cv::Mat& output);
  void compute_hough_circle(cv::Mat& image);
  void find_mode_parameter(int mode);

private:
  rad::Structure* radio_struct;

  vector<rad::structure::Circle> vec_circle;
};

}
