#pragma once

#include <Utility/Specific/Common.h>
#include <opencv2/opencv.hpp>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction::structure{class Circle;}
namespace rad::correction::image{class Image;}


namespace rad::correction::image{

class Hough
{
public:
  Hough(rad::correction::Node* node_correction);
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
  rad::correction::Structure* rad_struct;
  rad::correction::image::Image* rad_image;
};

}
