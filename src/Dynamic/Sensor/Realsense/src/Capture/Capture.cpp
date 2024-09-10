#include "Capture.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::capture{

//Constructor / Destructor
Capture::Capture(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(rlx::capture::Sensor& sensor){
  //---------------------------

  this->init_info(sensor);
  this->init_capture(sensor);

  //---------------------------
}
void Capture::capture(){
  //---------------------------

  // Wait for the next set of frames from the camera
  rs2::frameset frames = rlx_struct->pipe.wait_for_frames();

  // If successful, process and display the frames
  this->display(frames);

  //---------------------------
}

//Subfunction
void Capture::init_info(rlx::capture::Sensor& sensor){
  //---------------------------

  sensor.type_sensor = "capture";
  sensor.device.index = rlx_struct->current_ID++;
  sensor.name = "capture_" + std::to_string(sensor.device.index);
  sensor.calibration.path.insert("../media/calibration/kinect.json");

  sensor.info.model = "realsense";
  sensor.data->name = sensor.name;
  sensor.data->topology.type = utl::topology::POINT;
  sensor.data->nb_data_max = 10000000;
  sensor.data->path.directory = utl::path::get_current_path_abs();
  sensor.pose->model[2][3] = 1;

  //---------------------------
}
void Capture::init_capture(rlx::capture::Sensor& sensor){
  //---------------------------

  rs2::device_list devices = rlx_struct->context.query_devices(); // Get number of connected devices
  int nb_device = devices.size();
  if(nb_device != 0){
    rlx_struct->pipe.start();
  }

  //---------------------------
}
void Capture::display(rs2::frameset frames){
  //---------------------------

  // Get color and depth frames
  rs2::frame color_frame = frames.get_color_frame();
  rs2::depth_frame depth_frame = frames.get_depth_frame();

  if(!depth_frame){
    std::cerr << "Depth frame is empty!" << std::endl;
    return;
  }

  // Convert Realsense frames to OpenCV matrices
  const int w = color_frame.as<rs2::video_frame>().get_width();
  const int h = color_frame.as<rs2::video_frame>().get_height();

  // Create OpenCV matrices for color and depth images
  cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
  cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);

  if(depth.empty()){
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
