#include "Kinect.h"

#include "Struct_kinect.h"
#include "K4A_thread.h"
#include "K4A_device.h"


//Constructor / Destructor
Kinect::Kinect(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();
  this->k4a_thread = new K4A_thread(struct_kinect);
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::run(){
  //---------------------------

  //---------------------------
}

//Subfunction
void Kinect::make_k4a_configuration(){
  Struct_k4a_config& config = struct_kinect->config;
  Struct_k4a_color& color = struct_kinect->color;
  //---------------------------

  config.k4a_config.color_format = color.format;
  config.k4a_config.color_resolution = color.enabled ? color.resolution : K4A_COLOR_RESOLUTION_OFF;
  config.k4a_config.depth_mode = config.enable_camera_depth ? config.depth_mode : K4A_DEPTH_MODE_OFF;
  config.k4a_config.camera_fps = config.camera_fps;
  config.k4a_config.depth_delay_off_color_usec = config.depth_delay_off_color_usec;
  config.k4a_config.wired_sync_mode = config.wired_sync_mode;
  config.k4a_config.subordinate_delay_off_master_usec = config.subordinate_delay_off_master_usec;
  config.k4a_config.disable_streaming_indicator = config.disable_streaming_indicator;
  config.k4a_config.synchronized_images_only = config.synchronized_images_only;

  //---------------------------
}
void Kinect::start_camera(){
  //---------------------------

  //---------------------------
}
