#include "Kinect.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_thread.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


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
void Kinect::init(){
  //---------------------------


  //---------------------------
}
void Kinect::run(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr){return;}
  //---------------------------

  this->make_k4a_configuration(device);
  k4a_thread->start_thread(device);

  //---------------------------
}
void Kinect::loop(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr){return;}
  //---------------------------
/*
  // Assuming you have a k4a::capture object named 'capture'
  if(device->color.capture == nullptr){return;}
  k4a::image colorImage = device->color.capture.get_color_image();

  if (colorImage.is_valid()) {
      // Access the raw data
      const uint8_t* colorData = colorImage.get_buffer();

      // Now you can use colorData as needed

      // Don't forget to release the image when you are done with it
      colorImage.reset();
  }
*/
  //---------------------------
}

//Subfunction
void Kinect::make_k4a_configuration(Struct_k4a_device* device){
  //---------------------------

  k4a_device_configuration_t k4a_config;
  k4a_config.color_format = device->color.format;
  k4a_config.color_resolution = device->color.enabled ? device->color.resolution : K4A_COLOR_RESOLUTION_OFF;
  k4a_config.depth_mode = device->depth.enabled ? device->depth.mode : K4A_DEPTH_MODE_OFF;
  k4a_config.camera_fps = device->config.fps;
  k4a_config.depth_delay_off_color_usec = device->config.depth_delay_off_color_usec;
  k4a_config.wired_sync_mode = device->config.wired_sync_mode;
  k4a_config.subordinate_delay_off_master_usec = device->config.subordinate_delay_off_master_usec;
  k4a_config.disable_streaming_indicator = device->config.disable_streaming_indicator;
  k4a_config.synchronized_images_only = device->config.synchronized_images_only;

  //---------------------------
  device->config.k4a_config = k4a_config;
}
void Kinect::start_camera(){
  //---------------------------

  //---------------------------
}
