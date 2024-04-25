#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace radio{class Structure;}
namespace radio::structure{class Circle;}


namespace radio::detection{

class Hough
{
public:
  Hough(radio::Structure* radio_struct);
  ~Hough();

public:
  //Main function
  vector<radio::structure::Circle> sphere_detection(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void preprocessing(cv::Mat& input, cv::Mat& output);
  void compute_hough_circle(cv::Mat& image);
  void find_mode_parameter(int mode);

private:
  radio::Structure* radio_struct;

  vector<radio::structure::Circle> vec_circle;
};

}
