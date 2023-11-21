#include "CAP_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
CAP_capture::CAP_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->gui = gui;
  this->gui_stream = new GUI_stream(gui);

  //---------------------------
}
CAP_capture::~CAP_capture(){}

//Main function
void CAP_capture::design_panel(){
  //---------------------------

  this->draw_camera_color();

  //---------------------------
}

//Subfunction
void CAP_capture::draw_camera_color(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr) return;
  //---------------------------

  if(!device->is_capturing){return;}
  if(!device->capture->is_valid()){return;}
  k4a::image color_image = device->capture->get_color_image();
  if(!color_image.is_valid()){return;}

  uint8_t* color_data = color_image.get_buffer();
  int width = color_image.get_width_pixels();
  int height = color_image.get_height_pixels();
  gui_stream->draw_video(color_data, width, height);

  color_image.reset();

  //---------------------------
}
void CAP_capture::draw_camera_depth(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr) return;
  //---------------------------

  if(!device->is_capturing){return;}
  if(!device->capture->is_valid()){return;}
  k4a::image color_image = device->capture->get_depth_image();
  if(!color_image.is_valid()){return;}

  uint8_t* color_data = color_image.get_buffer();
  int width = color_image.get_width_pixels();
  int height = color_image.get_height_pixels();
  gui_stream->draw_video(color_data, width, height);

  color_image.reset();

  //---------------------------
}
void CAP_capture::draw_camera_ir(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr) return;
  //---------------------------

  if(!device->is_capturing){return;}
  if(!device->capture->is_valid()){return;}
  k4a::image color_image = device->capture->get_ir_image();
  if(!color_image.is_valid()){return;}

  uint8_t* color_data = color_image.get_buffer();
  int width = color_image.get_width_pixels();
  int height = color_image.get_height_pixels();
  gui_stream->draw_video(color_data, width, height);

  color_image.reset();

  //---------------------------
}
