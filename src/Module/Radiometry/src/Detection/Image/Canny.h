#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::detection::image{

class Canny
{
public:
  Canny(rad::Node* node_radio);
  ~Canny();

public:
  //Main function
  void apply_canny(cv::Mat& input, cv::Mat& output);

private:
  rad::Structure* rad_struct;
};

}
