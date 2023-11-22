#include "CAP_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_depth.h>


//Constructor / Destructor
CAP_capture::CAP_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_depth = new K4A_depth();
  this->gui = gui;

  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));

  //---------------------------
}
CAP_capture::~CAP_capture(){}

//Main function
void CAP_capture::design_panel(){
  //---------------------------

  //this->draw_camera_color();
  //this->draw_camera_depth();
  this->draw_camera_ir();

  //---------------------------
}

//Subfunction
void CAP_capture::draw_camera_color(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

  Struct_image struct_image;
  struct_image.buffer = device->data.color.buffer;
  struct_image.width = device->data.color.width;
  struct_image.height = device->data.color.height;
  struct_image.format = device->data.color.format;
  vec_gui_stream[0]->draw_stream(&struct_image);

  //---------------------------
}
void CAP_capture::draw_camera_depth(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

  Struct_image struct_image;
  struct_image.buffer = k4a_depth->convert_depth_into_color(device);
  struct_image.width = device->data.depth.width;
  struct_image.height = device->data.depth.height;
  struct_image.format = "R8G8B8A8_SRGB";
  vec_gui_stream[1]->draw_stream(&struct_image);

  //---------------------------
}
void CAP_capture::draw_camera_ir(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

  Struct_image struct_image;
  struct_image.buffer = device->data.ir.buffer;
  struct_image.width = device->data.ir.width;
  struct_image.height = device->data.ir.height;
  struct_image.format = "B8G8R8A8_SRGB";
  vec_gui_stream[2]->draw_stream(&struct_image);

  //---------------------------
}
