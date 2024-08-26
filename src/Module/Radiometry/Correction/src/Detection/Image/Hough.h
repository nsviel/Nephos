#pragma once
#include <opencv2/opencv.hpp>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor::structure{class Circle;}
namespace rad::cor::image{class Image;}
namespace utl::media{class Image;}


namespace rad::cor::image{

class Hough
{
public:
  Hough(rad::cor::Node* node_correction);
  ~Hough();

public:
  //Main function
  void detect_circle(cv::Mat& image, std::shared_ptr<utl::media::Image> output);

  //Hough function
  void compute_hough_circle(cv::Mat& image);
  void set_hough_mode(int mode);

  //Draw function
  void draw_detected_circle(cv::Mat& image, std::shared_ptr<utl::media::Image> output);
  void draw_all_circle(cv::Mat& image, std::shared_ptr<utl::media::Image> output);
  void draw_best_circle(cv::Mat& image, std::shared_ptr<utl::media::Image> output);

private:
  rad::cor::Structure* rad_struct;
  rad::cor::image::Image* rad_image;
};

}
