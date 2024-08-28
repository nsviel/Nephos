#include "Capture.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx{

//Constructor / Destructor
Capture::Capture(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(){
  //---------------------------

  // Start streaming with default settings
  //rlx_struct->pipe.start();

  //---------------------------
}
void Capture::capture(){
  //---------------------------

  // Wait for the next set of frames from the camera
  //rs2::frameset frames = rlx_struct->pipe.wait_for_frames();

  //this->display();

  //---------------------------
}
void Capture::display(rs2::frameset frames){
  //---------------------------

  // Get color and depth frames
  rs2::frame color_frame = frames.get_color_frame();
  rs2::depth_frame depth_frame = frames.get_depth_frame();

  if (!depth_frame) {
    std::cerr << "Depth frame is empty!" << std::endl;
    return;
  }

  // Convert Realsense frames to OpenCV matrices
  const int w = color_frame.as<rs2::video_frame>().get_width();
  const int h = color_frame.as<rs2::video_frame>().get_height();

  // Create OpenCV matrices for color and depth images
  cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
  cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);

  if (depth.empty()) {
    std::cerr << "Depth matrix is empty!" << std::endl;
    return;
  }

  // Convert color from RGB to BGR for OpenCV display
  cv::cvtColor(color, color, cv::COLOR_RGB2BGR);
  cv::imshow("Color Image", color);
/*
  // Normalize depth image for display
  cv::Mat depth_display;
  depth.convertTo(depth_display, CV_8UC1, 0.03);
  cv::imshow("Depth Image", depth_display);
*/

  //---------------------------
}



}
