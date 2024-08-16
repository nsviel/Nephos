#include "Class.h"

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx{

//Constructor / Destructor
Class::Class(){
  //---------------------------



  //---------------------------
}
Class::~Class(){}

//Main function
void Class::capture(){
  //---------------------------

  // Create a RealSense pipeline, which abstracts the device
  rs2::pipeline pipe;

  // Start streaming with default settings
  pipe.start();

  // Capture 30 frames to give autoexposure, etc. a chance to settle
  for (int i = 0; i < 30; i++){
    // Wait for the next set of frames from the camera
    rs2::frameset frames = pipe.wait_for_frames();
  }

  while (true){
    // Wait for the next set of frames from the camera
    rs2::frameset frames = pipe.wait_for_frames();

    // Get color and depth frames
    rs2::frame color_frame = frames.get_color_frame();
    rs2::depth_frame depth_frame = frames.get_depth_frame();

    // Convert RealSense frames to OpenCV matrices
    const int w = color_frame.as<rs2::video_frame>().get_width();
    const int h = color_frame.as<rs2::video_frame>().get_height();

    // Create OpenCV matrices for color and depth images
    cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
    cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);

    // Convert color from RGB to BGR for OpenCV display
    cv::cvtColor(color, color, cv::COLOR_RGB2BGR);

    // Normalize depth image for display
    cv::Mat depth_display;
    depth.convertTo(depth_display, CV_8UC1, 0.03);

    // Display the images
    cv::imshow("Color Image", color);
    cv::imshow("Depth Image", depth_display);

    // Exit on ESC key
    if (cv::waitKey(1) == 27){
      break;
    }
  }

  //---------------------------
}



}
