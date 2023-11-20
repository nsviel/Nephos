#include "K4A_capture.h"


//Constructor / Destructor
K4A_capture::K4A_capture(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();
  this->k4a_thread = new K4A_thread(struct_kinect);

  //---------------------------
}
K4A_capture::~K4A_capture(){}

//Main function
void K4A_capture::run(){
  //---------------------------

  //---------------------------
}

//Subfunction
void K4A_capture::open_selected_device(){
  //---------------------------

  try{
    if (selected_device_idx < 0){return;}
    selected_device = k4a::device::open(static_cast<uint32_t>(selected_device_idx));
  }
  catch (const int error){
    return;
  }

  //---------------------------
}
void K4A_capture::refresh_device_list(){
  //---------------------------

  //"(No available devices)"
  const uint32_t nb_device = k4a_device_get_installed_count();

  for (uint32_t i = 0; i < nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);
      connected_device.emplace_back(std::make_pair(i, device.get_serialnum()));
    }
    catch(const int error){
      continue;
    }
  }

  if (!connected_device.empty()){
    selected_device_idx = connected_device[0].first;
  }

  //---------------------------
}
void K4A_capture::make_k4a_configuration(Struct_kinect* config){
  //---------------------------

  config->k4a_config.color_format = config->color_format;
  config->k4a_config.color_resolution = config->enable_camera_color ? config->color_resolution : K4A_COLOR_RESOLUTION_OFF;
  config->k4a_config.depth_mode = config->enable_camera_depth ? config->depth_mode : K4A_DEPTH_MODE_OFF;
  config->k4a_config.camera_fps = config->camera_fps;
  config->k4a_config.depth_delay_off_color_usec = config->depth_delay_off_color_usec;
  config->k4a_config.wired_sync_mode = config->wired_sync_mode;
  config->k4a_config.subordinate_delay_off_master_usec = config->subordinate_delay_off_master_usec;
  config->k4a_config.disable_streaming_indicator = config->disable_streaming_indicator;
  config->k4a_config.synchronized_images_only = config->synchronized_images_only;

  //---------------------------
}
bool K4A_capture::start_camera(){
  //---------------------------

  if (camera_started){
    return false;
  }

  this->make_k4a_configuration(struct_kinect);
  selected_device.start_cameras(&struct_kinect->k4a_config);
  this->camera_started = true;

  /*this->thread_camera_polling = std14::make_unique<K4APollingThread>([selected_device, &camera_data_source, camera_pause, camera_started, false, false](bool firstRun){
    std::chrono::milliseconds pollingTimeout = CameraPollingTimeout;
    return PollSensor<k4a::capture>("Cameras", selected_device, &camera_data_source, camera_pause, camera_started, false,
      [](k4a::device *device, k4a::capture *capture, std::chrono::milliseconds timeout){return device->get_capture(capture, timeout);},
      [](k4a::device *device){device->stop_cameras();}, pollingTimeout);
  });*/

  return true;
}
