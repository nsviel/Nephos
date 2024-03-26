#pragma once

#include <Utility/Specific/common.h>
#include <opencv2/opencv.hpp>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::structure{class Circle;}


namespace k4n::detection{

class Hough
{
public:
  Hough(k4n::Node* node_k4n);
  ~Hough();

public:
  //Main function
  vector<k4n::structure::Circle> sphere_detection(cv::Mat& input, cv::Mat& output);

  //Subfunction
  void preprocessing(cv::Mat& input, cv::Mat& output);
  void compute_hough_circle(cv::Mat& image);
  void find_mode_parameter(int mode);

private:
  k4n::structure::K4N* k4n_struct;

  vector<k4n::structure::Circle> vec_circle;
};

}