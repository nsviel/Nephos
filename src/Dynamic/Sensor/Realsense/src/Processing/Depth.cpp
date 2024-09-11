#include "Depth.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Depth::Depth(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  //---------------------------

  // Get color and depth frames
  rs2::depth_frame frame_depth = rlx_sensor->device.frameset.get_depth_frame();
  if(!frame_depth) return;

  // Convert Realsense frames to OpenCV matrices
  const int w = frame_depth.as<rs2::video_frame>().get_width();
  const int h = frame_depth.as<rs2::video_frame>().get_height();

  // Create OpenCV matrices for color and depth images
  cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)frame_depth.get_data(), cv::Mat::AUTO_STEP);
  if(depth.empty()){
    std::cerr << "Depth matrix is empty!" << std::endl;
    return;
  }

  // Normalize depth image for display
  cv::Mat depth_normalized;
  depth.convertTo(depth_normalized, CV_8UC1, 255.0 / 10000.0);  // Adjust scaling based on depth range
/*
  // Apply false color (colormap) to the normalized depth image
  cv::Mat depth_colormap;
  cv::applyColorMap(depth_normalized, depth_colormap, cv::COLORMAP_JET);  // Use COLORMAP_JET or another colormap

  // Display depth image with false colors
  cv::imshow("Depth Image (False Color)", depth_colormap);

  // Wait for user input to close the window
  cv::waitKey(0);*/

  //---------------------------
}


}
