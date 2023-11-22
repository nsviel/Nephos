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
  this->draw_camera_depth();
  //this->draw_camera_ir();

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

void convertR16UintBufferToR8G8B8A8Srgb(uint8_t* inputBuffer) {
  size_t bufferSize = strlen(reinterpret_cast<const char*>(inputBuffer));
    uint8_t* outputBuffer = new uint8_t[bufferSize*4];


    for (size_t i = 0, j = 0; i < bufferSize; i=i+2, j += 4) {
        // Extract single-channel value (R)
        uint8_t r = inputBuffer[i];

        // Set R, G, B to the same value, and set A to 255
        outputBuffer[j] = r;       // R
        outputBuffer[j + 1] = r;   // G
        outputBuffer[j + 2] = r;   // B
        outputBuffer[j + 3] = 255; // A
    }

    *inputBuffer = *outputBuffer;
}

void CAP_capture::draw_camera_depth(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

convertR16UintBufferToR8G8B8A8Srgb(device->data.depth.buffer);

  Struct_image struct_image;
  struct_image.buffer = device->data.depth.buffer;
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
  struct_image.buffer = device->data.color.buffer;
  struct_image.width = device->data.color.width;
  struct_image.height = device->data.color.height;
  struct_image.format = "B8G8R8A8_SRGB";
  vec_gui_stream[2]->draw_stream(&struct_image);

  //---------------------------
}
