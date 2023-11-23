#include "K4A_capture.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
K4A_capture::K4A_capture(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
K4A_capture::~K4A_capture(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_capture::start_thread(Struct_k4a_device* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_capture::run_capture, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_capture::run_capture(Struct_k4a_device* device){
  if(device == nullptr) return;
  //---------------------------

  //Init
  k4a::device k4a_device = k4a::device::open(device->index);
  k4a::capture k4a_capture;
  k4a::record recording;

  //Start recording
  device->device = &k4a_device;
  device->config.version = k4a_device.get_version();
  k4a_device.start_cameras(&device->config.k4a_config);

  bool is_recording = thread_recording;
  if(is_recording){
    recording = k4a::record::create("output.mkv", k4a_device, device->config.k4a_config);
    recording.add_tag("Tag1", "Value1");
    recording.write_header();
  }

  this->thread_running = true;
  while(thread_running){
    k4a_device.get_capture(&k4a_capture, std::chrono::milliseconds(1000));
    device->temperature = k4a_capture.get_temperature_c();
    device->data.capture = &k4a_capture;

    if(is_recording){
      recording.write_capture(k4a_capture);
    }

    //Color
    k4a::image color = k4a_capture.get_color_image();
    device->data.color.name = "color";
    device->data.color.buffer = color.get_buffer();
    device->data.color.size = color.get_size();
    device->data.color.width = color.get_width_pixels();
    device->data.color.height = color.get_height_pixels();
    device->data.color.format = "B8G8R8A8_SRGB";
    device->data.color.timestamp = static_cast<float>(color.get_device_timestamp().count());
    color.reset();

    //Depth
    k4a::image depth = k4a_capture.get_depth_image();
    device->data.depth.name = "depth";
    device->data.depth.buffer = depth.get_buffer();
    device->data.depth.size = depth.get_size();
    device->data.depth.width = depth.get_width_pixels();
    device->data.depth.height = depth.get_height_pixels();
    device->data.depth.format = "B8G8R8A8_SRGB";
    device->data.depth.timestamp = static_cast<float>(depth.get_device_timestamp().count());
    depth.reset();

    //IR
    k4a::image ir = k4a_capture.get_ir_image();
    device->data.ir.name = "ir";
    device->data.ir.buffer = ir.get_buffer();
    device->data.ir.size = ir.get_size();
    device->data.ir.width = ir.get_width_pixels();
    device->data.ir.height = ir.get_height_pixels();
    device->data.ir.timestamp = static_cast<float>(ir.get_device_timestamp().count());
    ir.reset();

    device->data.data_ready = true;
  }

  k4a_device.stop_cameras();

  device->data.capture = nullptr;

  if(is_recording){
    recording.flush();
  }

  //---------------------------
}
void K4A_capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
