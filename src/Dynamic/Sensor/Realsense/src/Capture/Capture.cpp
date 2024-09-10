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
void Capture::capture(dat::base::Sensor& sensor){
  rlx::capture::Sensor* rlx_sensor = dynamic_cast<rlx::capture::Sensor*>(&sensor);
  //---------------------------

  // Wait for the next set of frames from the camera
  rlx_sensor->frameset = rlx_struct->pipe.wait_for_frames();

  // If successful, process and display the frames
  this->manage_color(*rlx_sensor);
  this->manage_depth(*rlx_sensor);

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
void Capture::manage_color(rlx::capture::Sensor& sensor){
  //---------------------------

  // Get color and depth frames
  rs2::frame frame_color = sensor.frameset.get_color_frame();


  std::shared_ptr<utl::media::Image> image = sensor.color.image;
  //---------------------------

  //Image
  image->name = "Color";
  image->data = std::vector<uint8_t>(sensor.color.data.buffer, sensor.color.data.buffer + sensor.color.data.size);
  image->size = image->data.size();
  image->width = sensor.color.data.width;
  image->height = sensor.color.data.height;
  image->format = sensor.color.data.format;
  image->timestamp = sensor.color.data.timestamp;
  dat_image->add_image(sensor, image);

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
void Capture::manage_depth(rlx::capture::Sensor& sensor){
  //---------------------------

  // Get color and depth frames
  rs2::depth_frame frame_depth = sensor.frameset.get_depth_frame();
  if(!frame_depth){
    std::cerr << "Depth frame is empty!" << std::endl;
    return;
  }

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

  // Apply false color (colormap) to the normalized depth image
  cv::Mat depth_colormap;
  cv::applyColorMap(depth_normalized, depth_colormap, cv::COLORMAP_JET);  // Use COLORMAP_JET or another colormap

  // Display depth image with false colors
  cv::imshow("Depth Image (False Color)", depth_colormap);

  // Wait for user input to close the window
  cv::waitKey(0);

  //---------------------------
}


}
