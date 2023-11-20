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
  Struct_k4a_device& device = struct_kinect->vec_device[0];
  //---------------------------

  k4a_device_configuration_t k4a_config;
  k4a_config.color_format = device.color.format;
  k4a_config.color_resolution = device.color.enabled ? device.color.resolution : K4A_COLOR_RESOLUTION_OFF;
  k4a_config.depth_mode = device.depth.enabled ? device.depth.mode : K4A_DEPTH_MODE_OFF;
  k4a_config.camera_fps = device.config.fps;
  k4a_config.depth_delay_off_color_usec = device.config.depth_delay_off_color_usec;
  k4a_config.wired_sync_mode = device.config.wired_sync_mode;
  k4a_config.subordinate_delay_off_master_usec = device.config.subordinate_delay_off_master_usec;
  k4a_config.disable_streaming_indicator = device.config.disable_streaming_indicator;
  k4a_config.synchronized_images_only = device.config.synchronized_images_only;

  //---------------------------
  device.config.k4a_config = k4a_config;
}
void Kinect::start_camera(){
  //---------------------------

  //---------------------------
}
