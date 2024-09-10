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
void Color::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  std::shared_ptr<utl::media::Image> image = rlx_sensor->image.color;
  //---------------------------

  /*
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
  */

  // Get color and depth frames
  rs2::frame frame_color = rlx_sensor->device.frameset.get_color_frame();

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
