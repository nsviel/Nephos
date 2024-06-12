#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace rad::detection::image{class Image;}


namespace rad::detection::image{

class Hough
{
public:
  Hough(rad::detection::Node* node_detection);
  ~Hough();

public:
  //Main function
  void detect_circle(cv::Mat& image, utl::media::Image* output);

  //Hough function
  void compute_hough_circle(cv::Mat& image);
  void set_hough_mode(int mode);

  //Draw function
  void draw_detected_circle(cv::Mat& image, utl::media::Image* output);
  void draw_all_circle(cv::Mat& image, utl::media::Image* output);
  void draw_best_circle(cv::Mat& image, utl::media::Image* output);

private:
  rad::detection::Structure* rad_struct;
  rad::detection::image::Image* rad_image;
};

}
