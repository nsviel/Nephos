#include "Color.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Color::Color(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::manage_color(rlx::base::Sensor& sensor){
  //---------------------------

  // Get color and depth frames
  rs2::frame frame_color = sensor.frameset.get_color_frame();

  // Convert Realsense frames to OpenCV matrices
  const int w = frame_color.as<rs2::video_frame>().get_width();
  const int h = frame_color.as<rs2::video_frame>().get_height();

  // Create OpenCV matrices for color and depth images
  cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)frame_color.get_data(), cv::Mat::AUTO_STEP);

  // Convert color from RGB to BGR for OpenCV display
  cv::cvtColor(color, color, cv::COLOR_RGB2BGR);
  cv::imshow("Color Image", color);

//cv::waitKey(0);

  //---------------------------
}

}
