#include "GUI_kinect_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>


//Constructor / Destructor
GUI_kinect_capture::GUI_kinect_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  this->gui_stream = new GUI_stream(gui);

  this->item_width = 100;

  //---------------------------
}
GUI_kinect_capture::~GUI_kinect_capture(){}

//Main function
void GUI_kinect_capture::draw_camera_color(Struct_k4a_device* device){
  if(device == nullptr) return;
  //---------------------------

  if(!device->is_capturing){return;}
  if(!device->capture->is_valid()){return;}
  k4a::image color_image = device->capture->get_color_image();
  //k4a::image color_image = device->capture->get_ir_image();
  //k4a::image color_image = device->capture->get_depth_image();
  if(!color_image.is_valid()){return;}

  uint8_t* color_data = color_image.get_buffer();
  int width = color_image.get_width_pixels();
  int height = color_image.get_height_pixels();
  gui_stream->draw_video(color_data, width, height);

  color_image.reset();

  //---------------------------
}
