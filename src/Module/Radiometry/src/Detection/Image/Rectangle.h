#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::detection::image{

class Rectangle
{
public:
  Rectangle(rad::Node* node_radio);
  ~Rectangle();

public:
  //Main function
  void detect_rectangle(cv::Mat& input, cv::Mat& output);
  void truc();

private:
  rad::Structure* rad_struct;
};

}
